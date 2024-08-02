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

#ifndef _PF_UTILS_MOVABLE_VALUE_hpp_
#define _PF_UTILS_MOVABLE_VALUE_hpp_

#include "include/utils/movable-value.hpp"

namespace pf
{
    template<typename T, T DefaultValue>
	constexpr MovableLiteral<T, DefaultValue>::MovableLiteral() : m_value(DefaultValue)
	{}

	template<typename T, T DefaultValue>
	template<typename U, typename>
	constexpr MovableLiteral<T, DefaultValue>::MovableLiteral(U&& value) : m_value(std::forward<U>(value))
	{}

	template<typename T, T DefaultValue>
	constexpr MovableLiteral<T, DefaultValue>::MovableLiteral(MovableLiteral&& val) noexcept : m_value(std::move(val.m_value))
	{
		val.m_value = DefaultValue;
	}

    template<typename T, T DefaultValue>
	constexpr T& MovableLiteral<T, DefaultValue>::get() &
	{
		return m_value;
	}

	template<typename T, T DefaultValue>
	constexpr T&& MovableLiteral<T, DefaultValue>::get() &&
	{
		return std::move(m_value);
	}

	template<typename T, T DefaultValue>
	constexpr const T& MovableLiteral<T, DefaultValue>::get() const &
	{
		return m_value;
	}

    template<typename T, T DefaultValue>
	constexpr MovableLiteral<T, DefaultValue>::operator T & () &
	{
		return m_value;
	}

	template<typename T, T DefaultValue>
	constexpr MovableLiteral<T, DefaultValue>::operator T && () &&
	{
		return std::move(m_value);
	}

	template<typename T, T DefaultValue>
	constexpr MovableLiteral<T, DefaultValue>::operator const T & () const &
	{
		return m_value;
	}

    template<typename T, T DefaultValue>
	template<typename U, typename>
	constexpr MovableLiteral<T, DefaultValue>& MovableLiteral<T, DefaultValue>::operator = (U&& value)
	{
		m_value = std::move(value);

		return *this;
	}

	template<typename T, T DefaultValue>
	constexpr MovableLiteral<T, DefaultValue>& MovableLiteral<T, DefaultValue>::operator = (MovableLiteral&& val) noexcept
	{
		std::swap(m_value, val.m_value);

		return *this;
	}

    template<typename T>
	template<typename U, typename>
	constexpr MovableValue<T>::MovableValue(U&& value) : m_value(std::forward<U>(value))
	{}

	template<typename T>
	constexpr MovableValue<T>::MovableValue(MovableValue&& val) noexcept : m_value(std::move(val.m_value))
	{}

    template<typename T>
	constexpr T& MovableValue<T>::get() &
	{
		return m_value;
	}

	template<typename T>
	constexpr T&& MovableValue<T>::get() &&
	{
		return std::move(m_value);
	}

	template<typename T>
	constexpr const T& MovableValue<T>::get() const &
	{
		return m_value;
	}

    template<typename T>
	constexpr MovableValue<T>::operator T & () &
	{
		return m_value;
	}

	template<typename T>
	constexpr MovableValue<T>::operator T && () &&
	{
		return std::move(m_value);
	}

	template<typename T>
	constexpr MovableValue<T>::operator const T & () const &
	{
		return m_value;
	}

    template<typename T>
	template<typename U, typename>
	constexpr MovableValue<T>& MovableValue<T>::operator = (U&& value)
	{
		m_value = std::move(value);
		return *this;
	}

	template<typename T>
	constexpr MovableValue<T>& MovableValue<T>::operator = (MovableValue&& val) noexcept
	{
		m_value = std::move(val.m_value);
		return *this;
	}
} // namespace pf

#endif // _PF_UTILS_MOVABLE_VALUE_hpp_