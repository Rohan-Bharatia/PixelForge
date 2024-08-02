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

#ifndef _PF_UTILS_ENDIANNESS_inl_
#define _PF_UTILS_ENDIANNESS_inl_

#include "include/utils/endianness.hpp"

namespace pf
{
    template<typename T>
    constexpr T big_endian_to_host(T value)
    {
    #if defined(PF_BIG_ENDIAN)

		return value;

    #elif defined(PF_LITTLE_ENDIAN)

		return byte_swap(value);

    #endif // defined(PF_BIG_ENDIAN)
    }

	template<typename T>
    constexpr T little_endian_to_host(T value)
    {
    #if defined(PF_BIG_ENDIAN)

		return byte_swap(value);

    #elif defined(PF_LITTLE_ENDIAN)

		return value;

    #endif // defined(PF_BIG_ENDIAN)
    }

	template<typename T>
    constexpr T host_to_big_endian(T value)
    {
        return big_endian_to_host(value);
    }

	template<typename T>
    constexpr T host_to_little_endian(T value)
    {
        return little_endian_to_host(value);
    }

} // namespace pf

#endif // _PF_UTILS_ENDIANNESS_inl_