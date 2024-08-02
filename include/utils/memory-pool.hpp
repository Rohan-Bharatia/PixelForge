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

#ifndef _PF_UTILS_MEMORY_POOL_hpp_
#define _PF_UTILS_MEMORY_POOL_hpp_

// std
#include <memory>
#include <vector>

#include "prerequisites.h"
#include "bitset.hpp"

namespace pf
{
    template<typename T, size_t Alignment, bool Const>
	class MemoryPoolIterator;

    template<typename T, size_t Alignment = alignof(T)>
	class MemoryPool
    {
    public:
        using iterator       = MemoryPoolIterator<T, Alignment, false>;
        using const_iterator = MemoryPoolIterator<T, Alignment, true>;
		friend iterator;
        friend const_iterator;

		class DeferConstruct {};
		class NoDestruction  {};

        MemoryPool(size_t block_size);
		MemoryPool(const MemoryPool&) = delete;
		MemoryPool(MemoryPool&&) noexcept = default;
		~MemoryPool();

        T* allocate(DeferConstruct, size_t& index);
		template<typename... Args>
        T* allocate(size_t& index, Args&&... args);

		void clear();

		void free(size_t index);
		void free(size_t index, NoDestruction);

		size_t get_allocated_entry_count() const;
		size_t get_block_count() const;
		size_t get_block_size() const;
		size_t get_free_entry_count() const;

		void reset();

		T* retrieve_from_index(size_t index);
		const T* retrieve_from_index(size_t index) const;
		size_t retrieve_entry_index(const T* data);

        iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;
		iterator end();
		const_iterator cend() const;
		const_iterator end() const;
		size_t size();

        MemoryPool& operator = (const MemoryPool&) = delete;
		MemoryPool& operator = (MemoryPool&& pool) noexcept = default;

		static constexpr DeferConstruct defer_construct = {};
		static constexpr size_t invalid_index = std::numeric_limits<size_t>::max();
		static constexpr NoDestruction no_destruction = {};

    private:
        void allocate_block();
		T* get_allocated_ptr(size_t block_index, size_t index);
		const T* get_allocated_ptr(size_t block_index, size_t index) const;
		std::pair<size_t, size_t> get_first_allocated_entry() const;
		std::pair<size_t, size_t> get_first_allocated_entry_from_block(size_t block_index) const;
		std::pair<size_t, size_t> get_next_allocated_entry(size_t block_index, size_t index) const;

		using aligned_storage = std::aligned_storage_t<sizeof(T), Alignment>;

		struct Block
		{
			size_t occupied_entry_count = 0;
			std::unique_ptr<aligned_storage[]> memory;
			Bitset<uint64> free_entries;
			Bitset<uint64> occupied_entries;
		};

		size_t m_block_size;
		std::vector<Block> m_blocks;
    };

    template<typename T, size_t Alignment, bool Const>
	class MemoryPoolIterator
	{
		using pool = MemoryPool<T, Alignment>;
		friend pool;

	public:
		using iterator_category = std::input_iterator_tag;
		using value_type = std::conditional_t<Const, const T, T>;
		using difference_type = std::ptrdiff_t;
		using ptr = value_type*;
		using reference = value_type&;

		MemoryPoolIterator(const MemoryPoolIterator&) = default;
		MemoryPoolIterator(MemoryPoolIterator&&) noexcept = default;

		size_t get_index() const;

		MemoryPoolIterator& operator = (const MemoryPoolIterator&) = default;
		MemoryPoolIterator& operator = (MemoryPoolIterator&&) noexcept = default;

		MemoryPoolIterator operator ++ (int);
		MemoryPoolIterator& operator ++ ();

		bool operator == (const MemoryPoolIterator& rhs) const;
		bool operator != (const MemoryPoolIterator& rhs) const;
		reference operator * () const;

	private:
		MemoryPoolIterator(std::conditional_t<Const, const pool, pool>* owner, size_t block_index, size_t local_index);

		size_t m_block_index;
		size_t m_index;
		std::conditional_t<Const, const Pool, Pool>* m_owner;
	};
} // namespace pf

#include "src/utils/memory-pool.inl"

#endif // _PF_UTILS_MEMORY_POOL_hpp_