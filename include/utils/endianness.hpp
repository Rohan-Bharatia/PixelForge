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

#ifndef _PF_UTILS_ENDIANNESS_hpp_
#define _PF_UTILS_ENDIANNESS_hpp_

// std
#include <cstddef>

#include "prerequisites.h"
#include "math-utils.hpp"

#if !defined(PF_BIG_ENDIAN) && !defined(PF_LITTLE_ENDIAN)

#if  defined(__m68k__) || defined(mc68000) || defined(_M_M68K) || (defined(__MIPS__) && defined(__MISPEB__)) \
 ||  defined(__ppc__) || defined(__POWERPC__) || defined(_M_PPC) || defined(__sparc__) || defined(__hppa__) \
 ||  defined(__BIG_ENDIAN__) || defined(__ARMEB__) || defined(__THUMBEB__) || defined(__AARCH64EB__) || defined(_MIPSEB) \
 ||  defined(__MIPSEB) || defined(__MIPSEB__) \
 || (defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) \
 || (defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && __BYTE_ORDER == __BIG_ENDIAN) \
 || (defined(BYTE_ORDER) && defined(BIG_ENDIAN) && BYTE_ORDER == BIG_ENDIAN)

#define PF_BIG_ENDIAN

#elif defined(__i386__) || defined(__i386) || defined(__X86__) || defined (__x86_64) || defined(_M_I86) \
   || defined(_M_IX86) || defined(_M_X64) || defined(__LITTLE_ENDIAN__) || defined(__ARMEL__) || defined(__THUMBEL__) \
   || defined(__AARCH64EL__) || defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__) \
   || (defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) \
   || (defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN) && __BYTE_ORDER == __LITTLE_ENDIAN) \
   || (defined(BYTE_ORDER) && defined(LITTLE_ENDIAN) && BYTE_ORDER == LITTLE_ENDIAN) \
   || defined(_WIN32)

#define PF_LITTLE_ENDIAN

#else /* (NOT) defined(__m68k__) || defined(mc68000) || defined(_M_M68K) || (defined(__MIPS__) && defined(__MISPEB__)) \
 ||  defined(__ppc__) || defined(__POWERPC__) || defined(_M_PPC) || defined(__sparc__) || defined(__hppa__) \
 ||  defined(__BIG_ENDIAN__) || defined(__ARMEB__) || defined(__THUMBEB__) || defined(__AARCH64EB__) || defined(_MIPSEB) \
 ||  defined(__MIPSEB) || defined(__MIPSEB__) \
 || (defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) \
 || (defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && __BYTE_ORDER == __BIG_ENDIAN) \
 || (defined(BYTE_ORDER) && defined(BIG_ENDIAN) && BYTE_ORDER == BIG_ENDIAN) */

#error Failed to identify endianness, you must define either PF_BIG_ENDIAN or PF_LITTLE_ENDIAN

#endif /* defined(__m68k__) || defined(mc68000) || defined(_M_M68K) || (defined(__MIPS__) && defined(__MISPEB__)) \
 ||  defined(__ppc__) || defined(__POWERPC__) || defined(_M_PPC) || defined(__sparc__) || defined(__hppa__) \
 ||  defined(__BIG_ENDIAN__) || defined(__ARMEB__) || defined(__THUMBEB__) || defined(__AARCH64EB__) || defined(_MIPSEB) \
 ||  defined(__MIPSEB) || defined(__MIPSEB__) \
 || (defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) \
 || (defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && __BYTE_ORDER == __BIG_ENDIAN) \
 || (defined(BYTE_ORDER) && defined(BIG_ENDIAN) && BYTE_ORDER == BIG_ENDIAN), defined(__i386__) || defined(__i386) || defined(__X86__) || defined (__x86_64) || defined(_M_I86) \
   || defined(_M_IX86) || defined(_M_X64) || defined(__LITTLE_ENDIAN__) || defined(__ARMEL__) || defined(__THUMBEL__) \
   || defined(__AARCH64EL__) || defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__) \
   || (defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) \
   || (defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN) && __BYTE_ORDER == __LITTLE_ENDIAN) \
   || (defined(BYTE_ORDER) && defined(LITTLE_ENDIAN) && BYTE_ORDER == LITTLE_ENDIAN) \
   || defined(_WIN32) */

#elif defined(PF_BIG_ENDIAN) && defined(PF_LITTLE_ENDIAN)

#error You cannot define both PF_BIG_ENDIAN and PF_LITTLE_ENDIAN

#endif // !defined(PF_BIG_ENDIAN) && !defined(PF_LITTLE_ENDIAN)

namespace pf
{
    enum class Endianness
    {
        BIG_ENDIAN,
        LITTLE_ENDIAN,
        
        UNKNOWN = 1,

        MAX = LITTLE_ENDIAN
    };

#if defined(PF_BIG_ENDIAN)

    constexpr Endianness platform_endianness = Endianness::BIG_ENDIAN;

#elif defined(PF_LITTLE_ENDIAN)

    constexpr Endianness platform_endianness = Endianness::LITTLE_ENDIAN;

#else // (NOT) defined(PF_BIG_ENDIAN), defined(PF_LITTLE_ENDIAN)

    constexpr Endianness platform_endianness = Endianness::UNKNOWN;

#endif // defined(PF_BIG_ENDIAN)

    template<typename T>
    constexpr T big_endian_to_host(T value);
	template<typename T>
    constexpr T little_endian_to_host(T value);

	template<typename T>
    constexpr T host_to_big_endian(T value);
	template<typename T>
    constexpr T host_to_little_endian(T value);

} // namespace pf

#include "src/utils/endianness.inl"

#endif // _PF_UTILS_ENDIANNESS_hpp_