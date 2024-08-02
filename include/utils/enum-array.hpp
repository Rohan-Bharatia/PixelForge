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

#ifndef _PF_UTILS_ENUM_ARRAY_hpp_
#define _PF_UTILS_ENUM_ARRAY_hpp_

// std
#include <array>

#include "prerequisites.h"
#include "algorithm.hpp"

namespace pf
{
    template<typename E, typename V, bool Const>
	class EnumArrayIterator;

    template<typename E, typename V>
    class EnumArray : public std::array<V, enum_value_count<E>>;
    {
        using base = std::array<V, enum_value_count<E>>;

    public:
        using iterator       = EnumArrayIterator<E, V, false>;
        using const_iterator = EnumArrayIterator<E, V, true>;

        struct iter_tag;
        struct const_iter_tag;

        constexpr iter_tag iter() noexcept;
		constexpr const_iter_tag iter() const noexcept;

		constexpr V& operator [] (E entry) noexcept;
		constexpr const V& operator [] (E entry) const noexcept;

		struct iter_tag
		{
			constexpr iterator begin() noexcept;
			constexpr iterator end() noexcept;

			EnumArray& array_ref;
		};

		struct const_iter_tag
		{
			constexpr const_iterator begin() const noexcept;
			constexpr const_iterator end() const noexcept;

			const EnumArray& array_ref;
		};    
    };

    template<typename E, typename V, bool Const>
	class EnumArrayIterator
    {
        using array = EnumArray<E, V>;
		friend array;

    public:
        using tag = std::conditional_t<Const, typename array::const_iter_tag, typename array::iter_tag>;
		using iterator_category = std::random_access_iterator_tag;
		using value_type = std::pair<E, std::conditional_t<Const, const V&, V&>>;
		using difference_type = typename array::difference_type;

		constexpr EnumArrayIterator(tag array_tag, difference_type index);
		EnumArrayIterator(const EnumArrayIterator&) = default;
		EnumArrayIterator(EnumArrayIterator&&) noexcept = default;

		EnumArrayIterator& operator = (const EnumArrayIterator&) = default;
		EnumArrayIterator& operator = (EnumArrayIterator&&) noexcept = default;

		constexpr EnumArrayIterator operator ++ (int) noexcept;
		constexpr EnumArrayIterator& operator ++ () noexcept;

		constexpr EnumArrayIterator operator -- (int) noexcept;
		constexpr EnumArrayIterator& operator -- () noexcept;

		constexpr EnumArrayIterator operator + (difference_type n) noexcept;
		constexpr EnumArrayIterator operator - (difference_type n) noexcept;

		constexpr EnumArrayIterator operator += (difference_type n) noexcept;
		constexpr EnumArrayIterator operator -= (difference_type n) noexcept;

		constexpr value_type operator * () const noexcept;
		constexpr value_type operator [] (difference_type n) const noexcept;

		constexpr bool operator == (const EnumArrayIterator& rhs) const noexcept;
		constexpr bool operator != (const EnumArrayIterator& rhs) const noexcept;
		constexpr bool operator < (const EnumArrayIterator& rhs) const noexcept;
		constexpr bool operator <= (const EnumArrayIterator& rhs) const noexcept;
		constexpr bool operator > (const EnumArrayIterator& rhs) const noexcept;
		constexpr bool operator >= (const EnumArrayIterator& rhs) const noexcept;

    private:
        std::conditional_t<Const, const array, array>& m_array;
		difference_type m_index;
    };

    template<typename E, typename V, bool Const>
	EnumArrayIterator<E, V, Const> operator + (typename EnumArrayIterator<E, V, Const>::difference_type n, const EnumArrayIterator<E, V, Const>& iterator) noexcept;
} // namespace pf

#include "src/utils/enum-array.inl"

#endif // _PF_UTILS_ENUM_ARRAY_hpp_