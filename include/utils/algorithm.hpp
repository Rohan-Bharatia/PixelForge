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

#ifndef _PF_UTILS_ALGORITHM_hpp_
#define _PF_UTILS_ALGORITHM_hpp_

// std
#include <cmath>
#include <memory>

#if __has_include(<version>)

// std
#include <version>

#endif // __has_include(<version>)

#include "prerequisites.h"
#include "constants-evaluated.h"
#include "type-traits.h"

#if defined(__cpp_lib_bit_cast) && __cpp_lib_bit_cast >= 201806L

#define PF_HAS_CONSTEXPR_BITCAST
#define PF_HAS_CONSTEXPR_BITCAST_STD
#define PF_CONSTEXPR_BITCAST constexpr

#elif PF_CHECK_MSVC_VER(1927) || PF_CHECK_CLANG_VER(1400) || PF_CHECK_GCC_VER(1100)

#define PF_HAS_CONSTEXPR_BITCAST
#define PF_HAS_CONSTEXPR_BITCAST_BUILTIN
#define PF_CONSTEXPR_BITCAST constexpr

#else // (NOT) defined(__cpp_lib_bit_cast) && __cpp_lib_bit_cast >= 201806L, PF_CHECK_MSVC_VER(1927) || PF_CHECK_CLANG_VER(1400) || PF_CHECK_GCC_VER(1100)

#define PF_CONSTEXPR_BITCAST

#endif // defined(__cpp_lib_bit_cast) && __cpp_lib_bit_cast >= 201806L

namespace pf
{
    template<typename T>
    [[nodiscard]] decltype(auto) access_by_offset(void* base_ptr, size_t offset) noexcept;
	template<typename T>
    [[nodiscard]] decltype(auto) access_by_offset(const void* base_ptr, size_t offset) noexcept;

	template<typename To, typename From>
    [[nodiscard]] PF_CONSTEXPR_BITCAST To bit_cast(const From& value) noexcept;

	template<typename T, size_t N>
    [[nodiscard]] constexpr size_t count_of(T(&name)[N]) noexcept;
	template<typename T> [[nodiscard]]
    constexpr size_t count_of(const T& c) noexcept;
	template<size_t N> [[nodiscard]]
    constexpr size_t count_of(const char(&str)[N]) noexcept;

	template<typename P, typename T>
    [[nodiscard]] PF_CONSTEXPR_BITCAST P int_2_ptr(T integer) noexcept;
	template<typename T, typename P>
    [[nodiscard]] PF_CONSTEXPR_BITCAST T ptr_2_int(P* ptr) noexcept;

	template<typename M, typename T>
    [[nodiscard]] auto& retrieve(M& map, const T& key) noexcept;
	template<typename M, typename T>
    [[nodiscard]] const auto& retrieve(const M& map, const T& key) noexcept;

	template<typename To, typename From>
    [[nodiscard]] To safe_cast(From&& value) noexcept;
	template<typename From> [[nodiscard]]
    auto safe_caster(From&& value) noexcept;

	template<typename T, typename U>
    [[nodiscard]] std::unique_ptr<T> static_unique_ptr_cast(std::unique_ptr<U>&& ptr) noexcept;

	template<typename T> [[nodiscard]]
    constexpr auto underlying_cast(T value) noexcept -> std::underlying_type_t<T>;
} // namespace pf

#include "src/utils/algorithm.inl"

#endif // _PF_UTILS_ALGORITHM_hpp_