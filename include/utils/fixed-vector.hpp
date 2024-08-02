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

#ifndef _PF_UTILS_FIXED_VECTOR_hpp_
#define _PF_UTILS_FIXED_VECTOR_hpp_

// std
#include <array>
#include <iterator>
#include <type_traits>

#include "memory-helper.hpp"
#include "movable-ptr.hpp"

namespace pf
{
    template<typename T, size_t Capacity>
	class FixedVector
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

		constexpr FixedVector();
		constexpr explicit FixedVector(size_t size, const T& value = T{});
		constexpr FixedVector(const FixedVector& vec);
		constexpr FixedVector(FixedVector&& vec) noexcept;
		~FixedVector();

		constexpr reference back();
		constexpr const_reference back() const;

		constexpr iterator begin() noexcept;
		constexpr const_iterator begin() const noexcept;

		constexpr void clear() noexcept;

		constexpr const_iterator cbegin() const noexcept;
		constexpr const_iterator cend() const noexcept;
		constexpr const_reverse_iterator crbegin() const noexcept;
		constexpr const_reverse_iterator crend() const noexcept;

		constexpr T* data() noexcept;
		constexpr T* data(size_type n) noexcept;
		constexpr const T* data() const noexcept;
		constexpr const T* data(size_type n) const noexcept;

		template<typename... Args> 
		constexpr iterator emplace(const_iterator pos, Args&&... args);

		template<typename... Args>
		constexpr reference emplace_back(Args&&... args);

		constexpr bool empty() const noexcept;

		constexpr iterator end() noexcept;
		constexpr const_iterator end() const noexcept;

		constexpr iterator erase(const_iterator pos);
		constexpr iterator erase(const_iterator first, const_iterator last);

		constexpr reference front() noexcept;
		constexpr const_reference front() const noexcept;

		constexpr iterator insert(const_iterator pos, const T& value);
		constexpr iterator insert(const_iterator pos, T&& value);

		constexpr size_type max_size() const noexcept;

		constexpr reference push_back(const T& value) noexcept(std::is_nothrow_copy_constructible<T>::value);
		constexpr reference push_back(T&& value) noexcept(std::is_nothrow_move_constructible<T>::value);

		constexpr void pop_back();

		constexpr void resize(size_type count);
		constexpr void resize(size_type count, const value_type& value);

		constexpr reverse_iterator rbegin() noexcept;
		constexpr const_reverse_iterator rbegin() const noexcept;

		constexpr reverse_iterator rend() noexcept;
		constexpr const_reverse_iterator rend() const noexcept;

		constexpr size_type size() const noexcept;

		constexpr reference operator [] (size_type pos);
		constexpr const_reference operator [] (size_type pos) const;

		constexpr FixedVector& operator = (const FixedVector& vec);
		constexpr FixedVector& operator = (FixedVector&& vec) noexcept;

		static constexpr size_type capacity() noexcept;

	private:
		alignas(T) std::array<std::byte, sizeof(T) * Capacity> m_data;
		size_t m_size;
	};
} // namespace pf

#include "src/utils/fixed-vector.inl"

#endif // _PF_UTILS_FIXED_VECTOR_hpp_