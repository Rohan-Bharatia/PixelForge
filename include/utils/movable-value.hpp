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

// std
#include <type_traits>

namespace pf
{
    template<typename T, T DefaultValue>
	class MovableLiteral
	{
	public:
		constexpr MovableLiteral();
		template<typename U, typename = std::enable_if_t<std::is_constructible_v<T, U>>>
        constexpr MovableLiteral(U&& value);
		constexpr MovableLiteral(const MovableLiteral&) = default;
		constexpr MovableLiteral(MovableLiteral&& val) noexcept;
		~MovableLiteral() = default;

		constexpr T& get() &;
		constexpr T&& get() &&;
		constexpr const T& get() const &;

		constexpr operator T & () &;
		constexpr operator T && () &&;
		constexpr operator const T & () const &;

		template<typename U, typename = std::enable_if_t<std::is_assignable_v<T&, U>>>
        constexpr MovableLiteral& operator = (U&& value);
		constexpr MovableLiteral& operator = (const MovableLiteral&) = default;
		constexpr MovableLiteral& operator = (MovableLiteral&& ptr) noexcept;

	private:
		T m_value;
	};

    template<typename T>
	class MovableValue
	{
		public:
			constexpr MovableValue() = default;
			template<typename U, typename = std::enable_if_t<std::is_constructible_v<T, U>>>
            constexpr MovableValue(U&& value);
			constexpr MovableValue(const MovableValue&) = default;
			constexpr MovableValue(MovableValue&& val) noexcept;
			~MovableValue() = default;

		constexpr T& get() &;
		constexpr T&& get() &&;
		constexpr const T& get() const &;

		constexpr operator T & () &;
		constexpr operator T && () &&;
		constexpr operator const T & () const &;

		template<typename U, typename = std::enable_if_t<std::is_assignable_v<T&, U>>>
        constexpr MovableValue& operator = (U&& value);
		constexpr MovableValue& operator = (const MovableValue&) = default;
		constexpr MovableValue& operator = (MovableValue&& val) noexcept;

	private:
		T m_value;
	};
} // namespace pf

#include "src/utils/movable-value.inl"

#endif // _PF_UTILS_MOVABLE_VALUE_hpp_