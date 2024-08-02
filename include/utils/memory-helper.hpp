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

#ifndef _PF_UTILS_MEMORY_HELPER_hpp_
#define _PF_UTILS_MEMORY_HELPER_hpp_

#include "prerequisites.h"

#if defined(PF_PLATFORM_WINDOWS)

#include <malloc.h>

#define PF_ALLOCA(size) _alloca(size)
#define PF_ALLOCA_SUPPORT

#elif defined(PF_COMPILER_CLANG) || defined(PF_COMPILER_GCC) || defined(PF_COMPILER_INTEL)

#ifdef PF_PLATFORM_BSD

#include <stdlib.h>

#else // (NOT) PF_PLATFORM_BSD

#include <alloca.h>

#endif // PF_PLATFORM_BSD

#define PF_ALLOCA(size) alloca(((size) > 0) ? (size) : 1)
#define PF_ALLOCA_SUPPORT

#endif // defined(PF_PLATFORM_WINDOWS)

#include <cstddef>

namespace pf
{
	template<typename T, typename... Args>
	constexpr T* placement_new(T* ptr, Args&&... args);

	template<typename T>
	constexpr void placement_destroy(T* ptr);
}

#include "src/utils/memory-helper.inl"

#endif // _PF_UTILS_MEMORY_HELPER_hpp_