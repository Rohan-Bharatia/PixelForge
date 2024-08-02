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

#ifndef _PF_UTILS_CONCEPTS_h_
#define _PF_UTILS_CONCEPTS_h_

// std
#include <type_traits>

#include "prerequisites.h"

#ifdef __cpp_concepts

#define PF_HAS_CONCEPTS

#if __has_include(<version>)
    
    #include <version>

#endif // __has_include(<version>)

#define PF_CONCEPT(arg) arg
#define PF_CONCEPT_T(arg) arg

#else // (NOT) __cpp_concepts

#define PF_CONCEPT(arg)
#define PF_CONCEPT_T(arg) typename

#endif // __cpp_concepts

#if defined(PF_HAS_CONCEPTS) && __cpp_lib_concepts

#include <concepts>

#define PF_HAS_STD_CONCEPTS
#define PF_STD_CONCEPT_T(arg) arg

#else // (NOT) defined(PF_HAS_CONCEPTS) && __cpp_lib_concepts

#define PF_STD_CONCEPT_T(arg) typename

#endif // defined(PF_HAS_CONCEPTS) && __cpp_lib_concepts

namespace pf
{
#ifdef PF_HAS_STD_CONCEPTS

    template<typename T>
    concept Arithmetic = std::is_arithmetic_v<T>;

#endif // PF_HAS_STD_CONCEPTS
} // namespace pf

#endif // _PF_UTILS_CONCEPTS_h_