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

#ifndef _PF_UTILS_CONSTANTS_hpp_
#define _PF_UTILS_CONSTANTS_hpp_

// std
#include <climits>
#include <limits>
#include <cmath>

#include "prerequisites.h"
#include "concepts.h"

namespace pf
{
    template<typename T> constexpr
    size_t bit_count = CHAR_BIT * sizeof(T);

    template<typename T>
    PF_CONCEPT(requires std::is_arithmetic_v<T> || std::is_void_v<T>)
	struct MathConstants
    {
        static constexpr T infinity()
		{
			static_assert(std::numeric_limits<T>::has_infinity);

			return std::numeric_limits<T>::infinity();
		}

		static constexpr T max()
		{
			return std::numeric_limits<T>::max();
		}

		static constexpr T min()
		{
			return std::numeric_limits<T>::min();
		}

		static constexpr T NaN()
		{
			static_assert(std::numeric_limits<T>::has_signaling_NaN);
			return std::numeric_limits<T>::quiet_NaN();
		}

		static constexpr T half_pi()
		{
			static_assert(std::is_floating_point_v<T>);
			return T(std::atan(1) * 2);
		}

		static constexpr T pi()
		{
			static_assert(std::is_floating_point_v<T>);
			return T(std::atan(1) * 4);
		}

		static constexpr T sqrt_2()
		{
			static_assert(std::is_floating_point_v<T>);
			return T(std::sqrt(2));
		}

		static constexpr T sqrt_3()
		{
			static_assert(std::is_floating_point_v<T>);
			return T(std::sqrt(3));
		}

		static constexpr T sqrt_5()
		{
			static_assert(std::is_floating_point_v<T>);
			return T(std::sqrt(5));
		}

		static constexpr T tau()
		{
			static_assert(std::is_floating_point_v<T>);
			return T(std::atan(1) * 8);
		}
    };

    template<typename T = void>
    constexpr auto infinity()
    {
        return MathConstants<T>::infinity();
    }

	template<typename T = void>
    constexpr auto max()
    {
        return MathConstants<T>::max();
    }

	template<typename T = void>
    constexpr auto min()
    {
        return MathConstants<T>::min();
    }

	template<typename T = void>
    constexpr auto NaN()
    {
        return MathConstants<T>::NaN();
    }

	template<typename T = void>
    constexpr auto half_pi()
    {
        return MathConstants<T>::half_pi();
    }
	
    template<typename T = void>
    constexpr auto pi()
    {
        return MathConstants<T>::pi();
    }
	
    template<typename T = void>
    constexpr auto sqrt_2()
    {
        return MathConstants<T>::sqrt_2();
    }
	
    template<typename T = void>
    constexpr auto sqrt_3()
    {
        return MathConstants<T>::sqrt_3();
    }
	
    template<typename T = void>
    constexpr auto sqrt_5()
    {
        return MathConstants<T>::sqrt_5();
    }
	
    template<typename T = void>
    constexpr auto tau()
    {
        return MathConstants<T>::tau();
    }
} // namespace pf

#include "src/utils/constants.inl"

#endif // _PF_UTILS_CONSTANTS_hpp_