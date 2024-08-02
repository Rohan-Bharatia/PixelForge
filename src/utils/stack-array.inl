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

#ifndef _PF_UTILS_STACK_ARRAY_inl_
#define _PF_UTILS_STACK_ARRAY_inl_

#include "include/utils/stack-array.hpp"

namespace pf
{
    template<typename T>
	StackArray<T>::StackArray() : m_size(0), m_ptr(nullptr)
	{}

	template<typename T>
	StackArray<T>::StackArray(T* stack_memory, size_t size) : m_size(size), m_ptr(stack_memory)
	{
		for(size_t i = 0; i < m_size; i++)
			placement_new(&m_ptr[i]);
	}

	template<typename T>
	StackArray<T>::StackArray(T* stack_memory, size_t size, NoInitTag) : m_size(size), m_ptr(stack_memory)
	{}

	template<typename T>
	StackArray<T>::~StackArray()
	{
		for(size_t i = 0; i < m_size; i++)
			placement_destroy(&m_ptr[i]);

	#ifndef PF_ALLOCA_SUPPORT

		operator_delete(m_ptr);

	#endif // PF_ALLOCA_SUPPORT
	}

	template<typename T>
	typename StackArray<T>::reference StackArray<T>::back()
	{
		assert(m_size != 0);

		return m_ptr[m_size - 1];
	}

	template<typename T>
	typename StackArray<T>::const_reference StackArray<T>::back() const
	{
		assert(m_size != 0);

		return m_ptr[m_size - 1];
	}

	template<typename T>
	typename StackArray<T>::iterator StackArray<T>::begin() noexcept
	{
		return iterator(&m_ptr[0]);
	}

	template<typename T>
	typename StackArray<T>::const_iterator StackArray<T>::begin() const noexcept
	{
		return const_iterator(&m_ptr[0]);
	}

	template<typename T>
	typename StackArray<T>::const_iterator StackArray<T>::cbegin() const noexcept
	{
		return const_iterator(&m_ptr[0]);
	}

	template<typename T>
	typename StackArray<T>::const_iterator StackArray<T>::cend() const noexcept
	{
		return const_iterator(&m_ptr[m_size]);
	}

	template<typename T>
	typename StackArray<T>::const_reverse_iterator StackArray<T>::crbegin() const noexcept
	{
		return const_reverse_iterator(&m_ptr[m_size]);
	}

	template<typename T>
	typename StackArray<T>::const_reverse_iterator StackArray<T>::crend() const noexcept
	{
		return const_reverse_iterator(&m_ptr[0]);
	}

	template<typename T>
	T* StackArray<T>::data() noexcept
	{
		return m_ptr;
	}

	template<typename T>
	const T* StackArray<T>::data() const noexcept
	{
		return m_ptr;
	}

	template<typename T>
	bool StackArray<T>::empty() const noexcept
	{
		return m_size == 0;
	}

	template<typename T>
	typename StackArray<T>::iterator StackArray<T>::end() noexcept
	{
		return iterator(&m_ptr[m_size]);
	}

	template<typename T>
	typename StackArray<T>::const_iterator StackArray<T>::end() const noexcept
	{
		return const_iterator(&m_ptr[m_size]);
	}

	template<typename T>
	void StackArray<T>::fill(const T& value)
	{
		std::fill(begin(), end(), value);
	}

	template<typename T>
	typename StackArray<T>::reference StackArray<T>::front() noexcept
	{
		return m_ptr[0];
	}

	template<typename T>
	typename StackArray<T>::const_reference StackArray<T>::front() const noexcept
	{
		return m_ptr[0];
	}

	template<typename T>
	typename StackArray<T>::size_type StackArray<T>::max_size() const noexcept
	{
		return size();
	}

	template<typename T>
	typename StackArray<T>::reverse_iterator StackArray<T>::rbegin() noexcept
	{
		return reverse_iterator(&m_ptr[m_size]);
	}

	template<typename T>
	typename StackArray<T>::const_reverse_iterator StackArray<T>::rbegin() const noexcept
	{
		return reverse_iterator(&m_ptr[m_size]);
	}

	template<typename T>
	typename StackArray<T>::reverse_iterator StackArray<T>::rend() noexcept
	{
		return reverse_iterator(&m_ptr[0]);
	}

	template<typename T>
	typename StackArray<T>::const_reverse_iterator StackArray<T>::rend() const noexcept
	{
		return reverse_iterator(&m_ptr[0]);
	}

	template<typename T>
	typename StackArray<T>::size_type StackArray<T>::size() const noexcept
	{
		return m_size;
	}

	template<typename T>
	typename StackArray<T>::reference StackArray<T>::operator [] (size_type pos)
	{
		assert(pos < m_size);
		return m_ptr[pos];
	}

	template<typename T>
	typename StackArray<T>::const_reference StackArray<T>::operator [] (size_type pos) const
	{
		assert(pos < m_size);

		return m_ptr[pos];
	}
} // namespace pf

#endif // _PF_UTILS_STACK_ARRAY_inl_