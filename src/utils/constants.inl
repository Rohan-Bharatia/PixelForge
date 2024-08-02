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

#ifndef _PF_UTILS_CONSTANTS_inl_
#define _PF_UTILS_CONSTANTS_inl_

#include "include/utils/constants.hpp"

namespace pf
{
    namespace Detail
    {
        #define PF_MATH_CONST(name)                                                                   \
        struct name##_caster                                                                          \
        {                                                                                             \
            template<typename To> PF_FORCEINLINE constexpr operator To() const { return name<To>(); } \
        }
        
        PF_MATH_CONST(infinity);
        PF_MATH_CONST(max);
        PF_MATH_CONST(min);
        PF_MATH_CONST(NaN);
        PF_MATH_CONST(half_pi);
        PF_MATH_CONST(pi);
        PF_MATH_CONST(sqrt_2);
        PF_MATH_CONST(sqrt_3);
        PF_MATH_CONST(sqrt_5);
        PF_MATH_CONST(tau);

        #undef PF_MATH_CONST
    } // namespace Detail
    
    template<>
	struct MathConstants<void>
	{
        PF_FORCEINLINE constexpr auto infinity()
        {
            return Detail::infinity_caster{};
        }
        
        PF_FORCEINLINE constexpr auto max()
        {
            return Detail::max_caster{};
        }
        
        PF_FORCEINLINE constexpr auto min()
        {
            return Detail::min_caster{};
        }
        
        PF_FORCEINLINE constexpr auto NaN()
        {
            return Detail::NaN_caster{};
        }
        
        PF_FORCEINLINE constexpr auto half_pi()
        {
            return Detail::half_pi_caster{};
        }
        
        PF_FORCEINLINE constexpr auto pi()
        {
            return Detail::pi_caster{};
        }
        
        PF_FORCEINLINE constexpr auto sqrt_2()
        {
            return Detail::sqrt_2_caster{};
        }
        
        PF_FORCEINLINE constexpr auto sqrt_3()
        {
            return Detail::sqrt_3_caster{};
        }
        
        PF_FORCEINLINE constexpr auto sqrt_5()
        {
            return Detail::sqrt_5_caster{};
        }
        
        PF_FORCEINLINE constexpr auto tau()
        {
            return Detail::tau_caster{}; 
        }
	};
} // namespace pf

#endif // _PF_UTILS_CONSTANTS_inl_