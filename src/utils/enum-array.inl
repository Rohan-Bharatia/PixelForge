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

#ifndef _PF_UTILS_ENUM_ARRAY_inl_
#define _PF_UTILS_ENUM_ARRAY_inl_

#include "include/utils/enum-array.hpp"

namespace pf
{
    template<typename E, typename V>
	constexpr auto EnumArray<E, V>::iter() noexcept -> iter_tag
	{
		return iter_tag{ *this };
	}

	template<typename E, typename V>
	constexpr auto EnumArray<E, V>::iter() const noexcept -> const_iter_tag
	{
		return const_iter_tag{ *this };
	}

	template<typename E, typename V>
	constexpr auto EnumArray<E, V>::operator [] (E entry) noexcept -> V&
	{
		return base::operator[](underlying_cast(entry));
	}

	template<typename E, typename V>
	constexpr auto EnumArray<E, V>::operator [] (E entry) const noexcept -> const V&
	{
		return base::operator[](underlying_cast(entry));
	}

    template<typename E, typename V> 
	constexpr typename EnumArray<E, V>::iterator EnumArray<E, V>::iter_tag::begin() noexcept
	{
		return EnumArray<E, V>::iterator(*this, 0);
	}

	template<typename E, typename V> 
	constexpr typename EnumArray<E, V>::iterator EnumArray<E, V>::iter_tag::end() noexcept
	{
		return EnumArray<E, V>::iterator(*this, array_ref.size());
	}

	template<typename E, typename V>
	constexpr typename EnumArray<E, V>::const_iterator EnumArray<E, V>::const_iter_tag::begin() const noexcept
	{
		return EnumArray<E, V>::const_iterator(*this, 0);
	}

	template<typename E, typename V>
	constexpr typename EnumArray<E, V>::const_iterator EnumArray<E, V>::const_iter_tag::end() const noexcept
	{
		return EnumArray<E, V>::const_iterator(*this, array_ref.size());
	}

    template<typename E, typename V, bool Const>
	constexpr EnumArrayIterator<E, V, Const>::EnumArrayIterator(tag array_tag, difference_type index) : m_array(array_tag.array_ref),
                                                                                                            m_index(index)
	{}

    template<typename E, typename V, bool Const>
	constexpr auto EnumArrayIterator<E, V, Const>::operator ++ (int) noexcept -> EnumArrayIterator
	{
		EnumArrayIterator it(*this);
		m_index++;

		return it;
	}

	template<typename E, typename V, bool Const>
	constexpr auto EnumArrayIterator<E, V, Const>::operator ++ () noexcept -> EnumArrayIterator&
	{
		m_index++;
		return *this;
	}

	template<typename E, typename V, bool Const>
	constexpr auto EnumArrayIterator<E, V, Const>::operator -- (int) noexcept -> EnumArrayIterator
	{
		EnumArrayIterator it(*this);
		m_index--;

		return it;
	}

	template<typename E, typename V, bool Const>
	constexpr auto EnumArrayIterator<E, V, Const>::operator -- () noexcept -> EnumArrayIterator&
	{
		m_index--;
		return *this;
	}

	template<typename E, typename V, bool Const>
	constexpr auto EnumArrayIterator<E, V, Const>::operator + (difference_type n) noexcept -> EnumArrayIterator
	{
		return EnumArrayIterator(m_array, m_index + n);
	}

	template<typename E, typename V, bool Const>
	constexpr auto EnumArrayIterator<E, V, Const>::operator - (difference_type n) noexcept -> EnumArrayIterator
	{
		return EnumArrayIterator(m_array, m_index - n);
	}

	template<typename E, typename V, bool Const>
	constexpr auto EnumArrayIterator<E, V, Const>::operator += (difference_type n) noexcept -> EnumArrayIterator
	{
		m_index += n;
		return *this;
	}

	template<typename E, typename V, bool Const>
	constexpr auto EnumArrayIterator<E, V, Const>::operator -= (difference_type n) noexcept -> EnumArrayIterator
	{
		m_index -= n;
		return *this;
	}

	template<typename E, typename V, bool Const>
	constexpr auto EnumArrayIterator<E, V, Const>::operator * () const noexcept -> value_type
	{
		E key = static_cast<E>(m_index);

		return std::make_pair(key, std::ref(m_array[key]));
	}

    template<typename E, typename V, bool Const>
	constexpr auto EnumArrayIterator<E, V, Const>::operator [] (difference_type n) const noexcept -> value_type
	{
		E key = static_cast<E>(m_index + n);

		return std::make_pair(key, std::ref(m_array[key]));
	}

	template<typename E, typename V, bool Const>
	constexpr bool EnumArrayIterator<E, V, Const>::operator == (const EnumArrayIterator& rhs) const noexcept
	{
		assert(&m_array == &rhs.m_array);

		return m_index == rhs.m_index;
	}
	
	template<typename E, typename V, bool Const>
	constexpr bool EnumArrayIterator<E, V, Const>::operator != (const EnumArrayIterator& rhs) const noexcept
	{
		assert(&m_array == &rhs.m_array);

		return m_index != rhs.m_index;
	}

	template<typename E, typename V, bool Const>
	constexpr bool EnumArrayIterator<E, V, Const>::operator < (const EnumArrayIterator& rhs) const noexcept
	{
		assert(&m_array == &rhs.m_array);

		return m_index < rhs.m_index;
	}

	template<typename E, typename V, bool Const>
	constexpr bool EnumArrayIterator<E, V, Const>::operator <= (const EnumArrayIterator& rhs) const noexcept
	{
		assert(&m_array == &rhs.m_array);

		return m_index <= rhs.m_index;
	}

	template<typename E, typename V, bool Const>
	constexpr bool EnumArrayIterator<E, V, Const>::operator > (const EnumArrayIterator& rhs) const noexcept
	{
		assert(&m_array == &rhs.m_array);

		return m_index > rhs.m_index;
	}

	template<typename E, typename V, bool Const>
	constexpr bool EnumArrayIterator<E, V, Const>::operator >= (const EnumArrayIterator& rhs) const noexcept
	{
		assert(&m_array == &rhs.m_array);

		return m_index >= rhs.m_index;
	}

    template<typename E, typename V, bool Const>
	EnumArrayIterator<E, V, Const> operator + (typename EnumArrayIterator<E, V, Const>::difference_type n, const EnumArrayIterator<E, V, Const>& iterator) noexcept
    {
        return iterator + n;
    }
} // namespace pf

#endif // _PF_UTILS_ENUM_ARRAY_inl_