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

#ifndef _PF_UTILS_STACK_ARRAY_hpp_
#define _PF_UTILS_STACK_ARRAY_hpp_

#include "memory-helper.hpp"
#include "movable-ptr.hpp"

#ifdef PF_ALLOCA_SUPPORT

#define pf_stack_array(T, size) pf::StackArray<T>(static_cast<T*>(PF_ALLOCA((size) * sizeof(T))), size)
#define pf_stack_array_no_init(T, size) pf::StackArray<T>(static_cast<T*>(PF_ALLOCA((size) * sizeof(T))), size, typename pf::StackArray<T>::NoInitTag())

#else // (NOT) PF_ALLOCA_SUPPORT

#define pf_stack_array(T, size) pf::StackArray<T>(static_cast<T*>(pf::operator_new((size) * sizeof(T))), size)
#define pf_stack_array_no_init(T, size) pf::StackArray<T>(static_cast<T*>(pf::operator_new((size) * sizeof(T))), size, typename pf::StackArray<T>::NoInitTag())

#endif // PF_ALLOCA_SUPPORT

namespace pf
{
    template<typename T>
    class StackArray
    {
    public:
		struct NoInitTag {};

		using value_type = T;
		using const_iterator = const value_type*;
		using const_ptr = const value_type*;
		using const_reference = const value_type&;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;
		using difference_type = std::ptrdiff_t;
		using iterator = value_type*;
		using ptr = value_type*;
		using reference = value_type&;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using size_type = size_t;

		StackArray();
		StackArray(T* stack_memory, size_t size);
		StackArray(T* stack_memory, size_t size, NoInitTag);
		StackArray(const StackArray&) = delete;
		StackArray(StackArray&&) = default;
		~StackArray();

		reference back();
		const_reference back() const;

		iterator begin() noexcept;
		const_iterator begin() const noexcept;

		const_iterator cbegin() const noexcept;
		const_iterator cend() const noexcept;
		const_reverse_iterator crbegin() const noexcept;
		const_reverse_iterator crend() const noexcept;

		T* data() noexcept;
		const T* data() const noexcept;

		bool empty() const noexcept;

		iterator end() noexcept;
		const_iterator end() const noexcept;

		void fill(const T& value);

		reference front() noexcept;
		const_reference front() const noexcept;

		size_type max_size() const noexcept;

		reverse_iterator rbegin() noexcept;
		const_reverse_iterator rbegin() const noexcept;

		reverse_iterator rend() noexcept;
		const_reverse_iterator rend() const noexcept;

		size_type size() const noexcept;

		reference operator [] (size_type pos);
		const_reference operator [] (size_type pos) const;

		StackArray& operator = (const StackArray&) = delete;
		StackArray& operator = (StackArray&&) = default;

	private:
		size_t m_size;
		MovablePtr<T> m_ptr;
    };
} // namespace pf

#include "src/utils/stack-array.inl"

#endif // _PF_UTILS_STACK_ARRAY_hpp_