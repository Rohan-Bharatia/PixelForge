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

#ifndef _PF_UTILS_MATH_UTILS_hpp_
#define _PF_UTILS_MATH_UTILS_hpp_

// std
#include <algorithm>
#include <cmath>
#include <limits>
#include <type_traits>

#include "prerequisites.h"
#include "algorithm.hpp"
#include "concepts.h"
#include "constants-evaluated.h"
#include "constants.hpp"

namespace pf
{
#if defined(PF_COMPILER_MSVC) || defined(PF_COMPILER_CLANG) || defined(PF_COMPILER_GCC)

	static constexpr bool has_fast_find_first_byte = true;

#else // (NOT) defined(PF_COMPILER_MSVC) || defined(PF_COMPILER_CLANG) || defined(PF_COMPILER_GCC)

	static constexpr bool has_fast_find_first_byte = false;

#endif // defined(PF_COMPILER_MSVC) || defined(PF_COMPILER_CLANG) || defined(PF_COMPILER_GCC)

    template<PF_STD_CONCEPT_T(std::integral) T1, PF_STD_CONCEPT_T(std::integral) T2>
    [[nodiscard]] constexpr T1 arithmetic_right_shift(T1 value, T2 shift) noexcept;

	template<PF_STD_CONCEPT_T(Arithmetic) T>
    [[nodiscard]] constexpr T byte_swap(T value) noexcept;

	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr T clear_bit(T number, T bit) noexcept;
	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] PF_CONSTEXPR20 size_t count_bits(T value) noexcept;
	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] PF_CONSTEXPR20 uint find_first_bit(T number) noexcept;
	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr T reverse_bits(T integer) noexcept;
	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr T set_bit(T number, T bit) noexcept;

	inline void swap_bytes(void* buffer, size_t size) noexcept;

	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr bool test_bit(T number, T bit) noexcept;
	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr T toggle_bit(T number, T bit) noexcept;

	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr T align(T offset, T alignment) noexcept;
	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr T align_2(T offset, T alignment) noexcept;

	template<typename T>
    [[nodiscard]] constexpr T approach(T value, T objective, T increment) noexcept;

	template<typename T>
    [[nodiscard]] constexpr T clamp(T value, T min, T max) noexcept;

	template<PF_STD_CONCEPT_T(std::floating_point) T>
    [[nodiscard]] constexpr T deg_2_rad(T degrees) noexcept;

	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr T get_nearest_power_of_2(T number) noexcept;
	
    template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr uint integral_log_2(T number) noexcept;
	
    template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr uint integral_log_2_pot(T pot) noexcept;
	
    template<typename T>
    [[nodiscard]] constexpr T integral_power(T base, uint exponent) noexcept;

	template<PF_STD_CONCEPT_T(std::floating_point) T>
    [[nodiscard]] PF_CONSTEXPR20 bool is_finite(T value) noexcept;
	template<PF_STD_CONCEPT_T(std::floating_point) T>
    [[nodiscard]] PF_CONSTEXPR20 bool is_infinity(T value) noexcept;
	template<PF_STD_CONCEPT_T(std::floating_point) T>
    [[nodiscard]] PF_CONSTEXPR20 bool is_NaN(T value) noexcept;
	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr bool is_pow2(T value) noexcept;

	template<typename T, typename T2>
    [[nodiscard]] constexpr T lerp(const T& from, const T& to, const T2& interpolation) noexcept;

	template<typename T>
    [[nodiscard]] constexpr T mod(T x, T y) noexcept;
	
    template<typename T>
    [[nodiscard]] constexpr T multiply_add(T x, T y, T z) noexcept;
	
    template<typename T>
    [[nodiscard]] constexpr bool number_equals(T a, T b) noexcept;
	
    template<typename T>
    [[nodiscard]] constexpr bool number_equals(T a, T b, T max_difference) noexcept;
	
    template<PF_STD_CONCEPT_T(std::floating_point) T>
    [[nodiscard]] constexpr T rad_2_deg(T radians) noexcept;

	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr T round_2_pow2(T value) noexcept;
} // namespace pf

#include "src/utils/math-utils.inl"

#endif // _PF_UTILS_MATH_UTILS_hpp_