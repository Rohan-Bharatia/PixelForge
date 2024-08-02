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

#ifndef _PF_UTILS_STACK_VECTOR_hpp_
#define _PF_UTILS_STACK_VECTOR_hpp_

#include "memory-helper.hpp"
#include "movable-ptr.hpp"

#ifdef PF_ALLOCA_SUPPORT

#define pf_stack_vector(T, capacity) pf::StackVector<T>(static_cast<T*>(PF_ALLOCA(capacity * sizeof(T))), capacity)

#else // (NOT) PF_ALLOCA_SUPPORT

#define pf_stack_vector(T, capacity) pf::StackVector<T>(static_cast<T*>(operator new (capacity * sizeof(T))), capacity)

#endif // PF_ALLOCA_SUPPORT

namespace pf
{
    template<typename T>
    class StackVector
    {
    public:
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

		StackVector();
		StackVector(T* stackMemory, size_t capacity);
		StackVector(const StackVector&) = delete;
		StackVector(StackVector&&) noexcept = default;
		~StackVector();

		reference back();
		const_reference back() const;

		iterator begin() noexcept;
		const_iterator begin() const noexcept;

		size_type capacity() const noexcept;

		void clear() noexcept;

		const_iterator cbegin() const noexcept;
		const_iterator cend() const noexcept;
		const_reverse_iterator crbegin() const noexcept;
		const_reverse_iterator crend() const noexcept;

		T* data() noexcept;
		const T* data() const noexcept;

		template<typename... Args>
		iterator emplace(const_iterator pos, Args&&... args);

		template<typename... Args>
		reference emplace_back(Args&&... args);

		bool empty() const noexcept;

		iterator end() noexcept;
		const_iterator end() const noexcept;

		iterator erase(const_iterator pos);
		iterator erase(const_iterator first, const_iterator last);

		reference front() noexcept;
		const_reference front() const noexcept;

		iterator insert(const_iterator pos, const T& value);
		iterator insert(const_iterator pos, T&& value);

		size_type max_size() const noexcept;

		reference push_back(const T& value) noexcept(std::is_nothrow_copy_constructible<T>::value);
		reference push_back(T&& value) noexcept(std::is_nothrow_move_constructible<T>::value);

		void pop_back();

		void resize(size_type count);
		void resize(size_type count, const value_type& value);

		reverse_iterator rbegin() noexcept;
		const_reverse_iterator rbegin() const noexcept;

		reverse_iterator rend() noexcept;
		const_reverse_iterator rend() const noexcept;

		size_type size() const noexcept;

		reference operator [] (size_type pos);
		const_reference operator [] (size_type pos) const;

		StackVector& operator = (const StackVector&) = delete;
		StackVector& operator = (StackVector&&) noexcept = default;

	private:
		size_t m_capacity;
		size_t m_size;
		MovablePtr<T> m_ptr;
    };
} // namespace pf

#include "src/utils/stack-vector.inl"

#endif // _PF_UTILS_STACK_VECTOR_hpp_