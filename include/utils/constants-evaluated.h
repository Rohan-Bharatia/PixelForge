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

#ifndef _PF_UTILS_CONSTANTS_EVALUATED_h_
#define _PF_UTILS_CONSTANTS_EVALUATED_h_

// std
#include <type_traits>

#include "prerequisites.h"

#if PF_CHECK_CPP_VER(PF_CPP23)

#define PF_HAS_CONSTEVAL
#define PF_CONSTEXPR20 constexpr
#define PF_IS_CONSTEVAL() consteval
#define PF_IS_RUNTIME_EVAL() !consteval

#elif PF_CHECK_CPP_VER(PF_CPP20)

#define PF_HAS_CONSTEVAL
#define PF_CONSTEXPR20 constexpr
#define PF_IS_CONSTEVAL() (std::is_constant_evaluated())
#define PF_IS_RUNTIME_EVAL() (!std::is_constant_evaluated())

#elif PF_CHECK_MSVC_VER(1925) || PF_CHECK_CLANG_VER(900) || PF_CHECK_GCC_VER(900)

#define PF_HAS_CONSTEVAL
#define PF_CONSTEXPR20 constexpr
#define PF_IS_CONSTEVAL() (__builtin_is_constant_evaluated())
#define PF_IS_RUNTIME_EVAL() (!__builtin_is_constant_evaluated())

#else // (NOT) PF_CHECK_CPP_VER(PF_CPP23), PF_CHECK_CPP_VER(PF_CPP20), PF_CHECK_MSVC_VER(1925) || PF_CHECK_CLANG_VER(900) || PF_CHECK_GCC_VER(900)

#define PF_CONSTEXPR20
#define PF_IS_CONSTEVAL() (false)
#define PF_IS_RUNTIME_EVAL() (true)

#endif // PF_CHECK_CPP_VER(PF_CPP23)

#endif // _PF_UTILS_CONSTANTS_EVALUATED_h_