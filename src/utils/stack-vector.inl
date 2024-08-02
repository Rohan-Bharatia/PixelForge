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

#ifndef _PF_UTILS_STACK_VECTOR_inl_
#define _PF_UTILS_STACK_VECTOR_inl_

#include "include/utils/stack-vector.hpp"

namespace pf
{
    template<typename T>
	StackVector<T>::StackVector() : m_capacity(0), m_size(0), m_ptr(nullptr)
	{
	}

	template<typename T>
	StackVector<T>::StackVector(T* stackMemory, size_t capacity) : m_capacity(capacity), m_size(0), m_ptr(stackMemory)
	{
	}

	template<typename T>
	StackVector<T>::~StackVector()
	{
		clear();

	#ifndef PF_ALLOCA_SUPPORT

		operator delete(m_ptr);

	#endif // PF_ALLOCA_SUPPORT
	}

    template<typename T>
	typename StackVector<T>::reference StackVector<T>::back()
	{
		assert(!empty());

		return m_ptr[m_size - 1];
	}

	template<typename T>
	typename StackVector<T>::const_reference StackVector<T>::back() const
	{
		assert(!empty());

		return m_ptr[m_size - 1];
	}

	template<typename T>
	typename StackVector<T>::iterator StackVector<T>::begin() noexcept
	{
		return iterator(&m_ptr[0]);
	}

	template<typename T>
	typename StackVector<T>::const_iterator StackVector<T>::begin() const noexcept
	{
		return const_iterator(&m_ptr[0]);
	}

	template<typename T>
	typename StackVector<T>::size_type StackVector<T>::capacity() const noexcept
	{
		return m_capacity;
	}

	template<typename T>
	void StackVector<T>::clear() noexcept
	{
		resize(0);
	}

	template<typename T>
	typename StackVector<T>::const_iterator StackVector<T>::cbegin() const noexcept
	{
		return const_iterator(&m_ptr[0]);
	}

	template<typename T>
	typename StackVector<T>::const_iterator StackVector<T>::cend() const noexcept
	{
		return const_iterator(&m_ptr[m_size]);
	}

	template<typename T>
	typename StackVector<T>::const_reverse_iterator StackVector<T>::crbegin() const noexcept
	{
		return const_reverse_iterator(&m_ptr[m_size]);
	}

	template<typename T>
	typename StackVector<T>::const_reverse_iterator StackVector<T>::crend() const noexcept
	{
		return const_reverse_iterator(&m_ptr[0]);
	}

	template<typename T>
	T* StackVector<T>::data() noexcept
	{
		return m_ptr;
	}

	template<typename T>
	const T* StackVector<T>::data() const noexcept
	{
		return m_ptr;
	}

	template<typename T>
	template<typename... Args>
	typename StackVector<T>::iterator StackVector<T>::emplace(const_iterator pos, Args&& ...args)
	{
		assert(m_size < m_capacity);
		assert(pos >= begin() && pos <= end());

		index = std::distance(cbegin(), pos);

		if(pos < end())
		{
			iterator lastElement = end() - 1;
			placement_new(&m_ptr[m_size], std::move(*lastElement));

			if(&m_ptr[index] < lastElement)
				std::move_backward(&m_ptr[index], &m_ptr[m_size - 1], &m_ptr[m_size]);

			placement_destroy(&m_ptr[index]);
		}

		m_size++;

		return placement_new(&m_ptr[index], std::forward<Args>(args)...);
	}

	template<typename T>
	template<typename... Args>
	typename StackVector<T>::reference StackVector<T>::emplace_back(Args&&... args)
	{

		assert(m_size < m_capacity);
		return *placement_new(&m_ptr[m_size++], std::forward<Args>(args)...);
	}

	template<typename T>
	bool StackVector<T>::empty() const noexcept
	{
		return m_size == 0;
	}

	template<typename T>
	typename StackVector<T>::iterator StackVector<T>::end() noexcept
	{
		return iterator(&m_ptr[m_size]);
	}

	template<typename T>
	typename StackVector<T>::const_iterator StackVector<T>::end() const noexcept
	{
		return const_iterator(&m_ptr[m_size]);
	}

	template<typename T>
	typename StackVector<T>::iterator StackVector<T>::erase(const_iterator pos)
	{
		assert(pos < end());
		index = std::distance(cbegin(), pos);
		std::move(begin() + index + 1, end(), begin() + index);
		pop_back();

		return iterator(&m_ptr[index]);
	}

	template<typename T>
	typename StackVector<T>::iterator StackVector<T>::erase(const_iterator first, const_iterator last)
	{
		 index = std::distance(cbegin(), first);

		if(first == last)
			return begin() + index;

		assert(first < last);
		assert(first >= begin() && last <= end());

		 count = std::distance(first, last);

		std::move(begin() + index + count, end(), begin() + index);
		resize(size() - count);

		return iterator(&m_ptr[index]);
	}

	template<typename T>
	typename StackVector<T>::reference StackVector<T>::front() noexcept
	{
		assert(!empty());

		return m_ptr[0];
	}

	template<typename T>
	typename StackVector<T>::const_reference StackVector<T>::front() const noexcept
	{
		assert(!empty());

		return m_ptr[0];
	}

	template<typename T>
	typename StackVector<T>::iterator StackVector<T>::insert(const_iterator pos, const T& value)
	{
		return emplace(pos, value);
	}

	template<typename T>
	typename StackVector<T>::iterator StackVector<T>::insert(const_iterator pos, T&& value)
	{
		return emplace(pos, std::move(value));
	}

	template<typename T>
	typename StackVector<T>::size_type StackVector<T>::max_size() const noexcept
	{
		return capacity();
	}

	template<typename T>
	typename StackVector<T>::reference StackVector<T>::push_back(const T& value) noexcept(std::is_nothrow_copy_constructible<T>::value)
	{
		assert(m_size < m_capacity);

		return *placement_new(&m_ptr[m_size++], value);
	}

	template<typename T>
	typename StackVector<T>::reference StackVector<T>::push_back(T&& value) noexcept(std::is_nothrow_move_constructible<T>::value)
	{
		assert(m_size < m_capacity);

		return *placement_new(&m_ptr[m_size++], std::move(value));
	}

	template<typename T>
	void StackVector<T>::pop_back()
	{
		assert(!empty());

		placement_destroy(&m_ptr[--m_size]);
	}

	template<typename T>
	void StackVector<T>::resize(size_type count)
	{
		assert(count <= m_capacity);

		if (count > m_size)
		{
			for(i = m_size; i < count; i++)
				placement_new(&m_ptr[i]);

			m_size = count;
		}
		else if (count < m_size)
		{
			for(i = count; i < m_size; i++)
				placement_destroy(&m_ptr[i]);

			m_size = count;
		}
	}

	template<typename T>
	void StackVector<T>::resize(size_type count, const value_type& value)
	{
		assert(count <= m_capacity);

		if(count > m_size)
		{
			for(i = m_size; i < count; i++)
				placement_new(&m_ptr[i], value);

			m_size = count;
		}
		else if(count < m_size)
		{
			for(i = count; i < m_size; i++)
				placement_destroy(&m_ptr[i]);

			m_size = count;
		}
	}

	template<typename T>
	typename StackVector<T>::reverse_iterator StackVector<T>::rbegin() noexcept
	{
		return reverse_iterator(&m_ptr[m_size]);
	}

	template<typename T>
	typename StackVector<T>::const_reverse_iterator StackVector<T>::rbegin() const noexcept
	{
		return reverse_iterator(&m_ptr[m_size]);
	}

	template<typename T>
	typename StackVector<T>::reverse_iterator StackVector<T>::rend() noexcept
	{
		return reverse_iterator(&m_ptr[0]);
	}

	template<typename T>
	typename StackVector<T>::const_reverse_iterator StackVector<T>::rend() const noexcept
	{
		return reverse_iterator(&m_ptr[0]);
	}

	template<typename T>
	typename StackVector<T>::size_type StackVector<T>::size() const noexcept
	{
		return m_size;
	}

	template<typename T>
	typename StackVector<T>::reference StackVector<T>::operator [] (size_type pos)
	{
		assert(pos < m_size);
		return m_ptr[pos];
	}

	template<typename T>
	typename StackVector<T>::const_reference StackVector<T>::operator [] (size_type pos) const
	{
		assert(pos < m_size);
		return m_ptr[pos];
	}
} // namespace pf

#endif // _PF_UTILS_STACK_VECTOR_inl_