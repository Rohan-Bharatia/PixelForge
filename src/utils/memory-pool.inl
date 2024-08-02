#pragma region LICENSE

//                    GNU GENERAL PUBLIC LICENSE
//                       Version 3, 29 June 2007
// 
// Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
// Everyone is permitted to copy and distribute verbatim copies
// of this license document, but changing it is not allowed.
// 
//                                   ...
// 
//                    Copyright (C) Rohan Bharatia 2024

#pragma endregion LICENSE

#pragma once

#ifndef _PF_UTILS_MEMORY_POOL_inl_
#define _PF_UTILS_MEMORY_POOL_inl_

#include "include/utils/memory-pool.hpp"

namespace pf
{
    template<typename T, size_t Alignment>
	MemoryPool<T, Alignment>::MemoryPool(size_t block_size) : m_block_size(block_size)
	{
		allocate_block();
	}

    template<typename T, size_t Alignment>
	MemoryPool<T, Alignment>::~MemoryPool()
	{
		reset();
	}

    template<typename T, size_t Alignment>
	T* MemoryPool<T, Alignment>::allocate(DeferConstruct, size_t& index)
	{
		size_t block_index = 0;
		size_t index = invalid_index;

		for(; block_index < m_blocks.size(); block_index++)
		{
			auto& block = m_blocks[block_index];

			if(block.occupied_entry_count == m_block_size)
				continue;

			index = block.free_entries.find_first();
			assert(index != block.free_entries.npos);
			break;
		}

		if(block_index >= m_blocks.size())
		{
			block_index = m_blocks.size();
			index = 0;

			allocate_block();
		}

		assert(index != invalid_index);

		auto& block = m_blocks[block_index];
		block.free_entries.reset(index);
		block.occupied_entries.Set(index);
		block.occupied_entry_count++;

		T* entry = std::launder(reinterpret_cast<T*>(&block.memory[index]));

		index = block_index * m_block_size + local_index;

		return entry;
	}

    template<typename T, size_t Alignment>
	template<typename... Args>
	T* MemoryPool<T, Alignment>::allocate(size_t& index, Args&&... args)
	{
		T* entry = allocate(DeferConstruct, index);
		placement_new(entry, std::forward<Args>(args)...);

		return entry;
	}

    template<typename T, size_t Alignment>
	void MemoryPool<T, Alignment>::clear()
	{
		reset();

		m_blocks.clear();
	}

    template<typename T, size_t Alignment>
	void MemoryPool<T, Alignment>::free(size_t index)
	{
		size_t block_index = index / m_block_size;
		size_t local_index = index % m_block_size;

		T* entry = get_allocated_ptr(block_index, local_index);
		placement_destroy(entry);

		auto& block = m_blocks[block_index];
		assert(block.occupied_entry_count > 0);
		block.occupied_entry_count--;

		block.free_entries.set(local_index);
		block.occupied_entries.reset(local_index);
	}
	
	template<typename T, size_t Alignment>
	void MemoryPool<T, Alignment>::free(size_t index, NoDestruction)
	{
		size_t block_index = index / m_block_size;
		size_t local_index = index % m_block_size;

		auto& block = m_blocks[block_index];
		assert(block.occupied_entry_count > 0);
		block.occupied_entry_count--;

		block.free_entries.set(local_index);
		block.occupied_entries.reset(local_index);
	}

	template<typename T, size_t Alignment>
	size_t MemoryPool<T, Alignment>::get_allocated_entry_count() const
	{
		size_t count = 0;
		for(auto& block : m_blocks)
			count += block.occupied_entry_count;

		return count;
	}

    template<typename T, size_t Alignment>
	size_t MemoryPool<T, Alignment>::get_block_count() const
	{
		return m_blocks.size();
	}

	template<typename T, size_t Alignment>
	size_t MemoryPool<T, Alignment>::get_block_size() const
	{
		return m_block_size;
	}

	template<typename T, size_t Alignment>
	size_t MemoryPool<T, Alignment>::get_free_entry_count() const
	{
		size_t count = m_blocks.size() * m_block_size;

		return count - get_allocated_entry_count();
	}

	template<typename T, size_t Alignment>
	void MemoryPool<T, Alignment>::reset()
	{
		for(size_t block_index = 0; block_index < m_blocks.size(); block_index++)
		{
			auto& block = m_blocks[block_index];
			if(block.occupied_entry_count == 0)
				continue;

			for(size_t index = block.occupied_entries.find_first(); index != block.occupied_entries.npos; index = block.occupied_entries.find_next(index))
			{
				T* entry = std::launder(reinterpret_cast<T*>(&m_blocks[block_index].memory[index]));
				placement_destroy(entry);
			}

			block.free_entries.reset(true);
			block.occupied_entries.reset(false);
			block.occupied_entry_count = 0;
		}
	}

    template<typename T, size_t Alignment>
	T* MemoryPool<T, Alignment>::retrieve_from_index(size_t index)
	{
		size_t block_index = index / m_block_size;
		size_t local_index = index % m_block_size;

		return GetAllocatedPointer(block_index, local_index);
	}

	template<typename T, size_t Alignment>
	const T* MemoryPool<T, Alignment>::retrieve_from_index(size_t index) const
	{
		size_t block_index = index / m_block_size;
		size_t local_index = index % m_block_size;

		return GetAllocatedPointer(block_index, local_index);
	}

	template<typename T, size_t Alignment>
	size_t MemoryPool<T, Alignment>::retrieve_entry_index(const T* data)
	{
		size_t block_index = 0;
		size_t local_index = invalid_index;

		for(; block_index < m_blocks.size(); block_index++)
		{
			auto& block = m_blocks[block_index];
			const T* start = reinterpret_cast<const T*>(&block.memory[0]);

			if(data >= start && data < start + m_blockSize)
			{
				local_index = safe_cast<size_t>(data - start);
				assert(data == reinterpret_cast<const T*>(&block.memory[local_index]));

				break;
			}
		}

		if(block_index == m_blocks.size())
			return invalid_index;

		assert(local_index != invalid_index);

		return block_index * m_block_size + local_index;
	}

    template<typename T, size_t Alignment>
	auto MemoryPool<T, Alignment>::begin() -> iterator
	{
		auto [block_index, local_index] = get_first_allocated_entry();
		return iterator(this, block_index, local_index);
	}

	template<typename T, size_t Alignment>
	auto MemoryPool<T, Alignment>::begin() const -> const_iterator
	{
		return cbegin();
	}

	template<typename T, size_t Alignment>
	auto MemoryPool<T, Alignment>::cbegin() const -> const_iterator
	{
		auto [block_index, local_index] = get_first_allocated_entry();
		return const_iterator(this, block_index, local_index);
	}

	template<typename T, size_t Alignment>
	auto MemoryPool<T, Alignment>::end() -> iterator
	{
		return iterator(this, invalid_index, invalid_index);
	}

	template<typename T, size_t Alignment>
	auto MemoryPool<T, Alignment>::end() const -> const_iterator
	{
		return cend();
	}

	template<typename T, size_t Alignment>
	auto MemoryPool<T, Alignment>::cend() const -> const_iterator
	{
		return const_iterator(this, invalid_index, invalid_index);
	}

	template<typename T, size_t Alignment>
	size_t MemoryPool<T, Alignment>::size()
	{
		return get_allocated_entry_count();
	}

	template<typename T, size_t Alignment>
	void MemoryPool<T, Alignment>::allocate_block()
	{
		auto& block = m_blocks.emplace_back();
		block.free_entries.resize(m_block_size, true);
		block.occupied_entries.resize(m_block_size, false);
		block.memory = std::make_unique<aligned_storage[]>(m_block_size);
	}

	template<typename T, size_t Alignment>
	T* MemoryPool<T, Alignment>::get_allocated_ptr(size_t block_index, size_t local_index)
	{
		assert(block_index < m_blocks.size());
		auto& block = m_blocks[block_index];
		assert(block.occupied_entries.test(local_index));

		return std::launder(reinterpret_cast<T*>(&block.memory[local_index]));
	}

	template<typename T, size_t Alignment>
	const T* MemoryPool<T, Alignment>::get_allocated_ptr(size_t block_index, size_t local_index) const
	{
		assert(block_index < m_blocks.size());
		auto& block = m_blocks[block_index];
		assert(block.occupied_entries.test(local_index));

		return std::launder(reinterpret_cast<const T*>(&block.memory[local_index]));
	}

	template<typename T, size_t Alignment>
	std::pair<size_t, size_t> MemoryPool<T, Alignment>::get_first_allocated_entry() const
	{
		return get_first_allocated_entry_from_block(0);
	}

    template<typename T, size_t Alignment>
	std::pair<size_t, size_t> MemoryPool<T, Alignment>::get_first_allocated_entry_from_block(size_t block_index) const
	{
		size_t local_index = invalid_index;

		for(; block_index < m_blocks.size(); block_index++)
		{
			auto& block = m_blocks[block_index];
			if(block.occupied_entry_count == 0)
				continue;

			local_index = block.occupied_entries.FindFirst();
			assert(local_index != block.occupied_entries.npos);
			break;
		}

		if(block_index >= m_blocks.size())
			return { invalid_index, invalid_index };

		return { block_index, local_index };
	}

	template<typename T, size_t Alignment>
	std::pair<size_t, size_t> MemoryPool<T, Alignment>::get_next_allocated_entry(size_t block_index, size_t local_index) const
	{
		assert(block_index < m_blocks.size());
		auto& block = m_blocks[block_index];
		size_t next = block.occupied_entries.find_next(local_index);
		if(next != block.occupied_entries.npos)
			return { block_index, next };

		return get_first_allocated_entry_from_block(block_index + 1);
	}

    template<typename T, size_t Alignment, bool Const>
	MemoryPoolIterator<T, Alignment, Const>::MemoryPoolIterator(std::conditional_t<Const, const pool, pool>* owner, size_t block_index, size_t local_index) :
	    m_block_index(block_index), m_local_index(local_index), m_owner(owner)
	{}

	template<typename T, size_t Alignment, bool Const>
	size_t MemoryPoolIterator<T, Alignment, Const>::get_index() const
	{
		assert(m_block_index != pool::invalid_index);
		assert(m_local_index != pool::invalid_index);
		return m_block_index * m_owner->get_block_size() + m_local_index;
	}

	template<typename T, size_t Alignment, bool Const>
	auto MemoryPoolIterator<T, Alignment, Const>::operator ++ (int) -> MemoryPoolIterator
	{
		MemoryPoolIterator copy(*this);
		operator ++ ();

		return copy;
	}

	template<typename T, size_t Alignment, bool Const>
	auto MemoryPoolIterator<T, Alignment, Const>::operator ++ () -> MemoryPoolIterator&
	{
		auto [block_index, local_index] = m_owner->get_next_allocated_entry(m_block_index, m_local_index);
		m_block_index = block_index;
		m_local_index = local_index;

		return *this;
	}

	template<typename T, size_t Alignment, bool Const>
	bool MemoryPoolIterator<T, Alignment, Const>::operator == (const MemoryPoolIterator& rhs) const
	{
		assert(m_owner == rhs.m_owner);

		return m_block_index == rhs.m_block_index && m_local_index == rhs.m_local_index;
	}

	template<typename T, size_t Alignment, bool Const>
	bool MemoryPoolIterator<T, Alignment, Const>::operator != (const MemoryPoolIterator& rhs) const
	{
		return !operator == rhs;
	}

	template<typename T, size_t Alignment, bool Const>
	auto MemoryPoolIterator<T, Alignment, Const>::operator * () const -> reference
	{
		return *m_owner->get_allocated_ptr(m_block_index, m_local_index);
	}
} // namespace pf

#endif // _PF_UTILS_MEMORY_POOL_inl_