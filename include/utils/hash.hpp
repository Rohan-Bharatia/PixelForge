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

#ifndef _PF_UTILS_HASH_hpp_
#define _PF_UTILS_HASH_hpp_

// std
#include <string_view>

#include "prerequisites.h"

namespace pf
{
    template<typename T>
    void hash_combine(size_t& seed, const T& v);
	template<typename T, typename... Args>
    size_t hash_combine(const T& v, const Args&... args);

    template<typename T>
	struct HashFunctor
	{
		template<typename... Args>
        size_t operator () (Args&&... args);
	};

    template<typename T>
    constexpr T CRC(const char* str) noexcept;
	template<typename T>
    constexpr T CRC(std::string_view str) noexcept;
	template<typename T>
    constexpr T CRC(const uint8* data, size_t size) noexcept;
	template<typename T, size_t N>
    constexpr T CRC(const char(&str)[N]) noexcept;

    template<typename T>
    struct CRCHash
	{
		template<typename... Args>
        T operator () (Args&&... args);
	};

	template<typename T>
    constexpr T FNV1a(const char* str) noexcept;
	template<typename T>
    constexpr T FNV1a(std::string_view str) noexcept;
	template<typename T>
    constexpr T FNV1a(const uint8* data, size_t size) noexcept;
	template<typename T, size_t N>
    constexpr T FNV1a(const char(&str)[N]) noexcept;

    template <typename T>
    struct FNV1aHash
	{
		template<typename... Args>
        T operator () (Args&&... args);
	};
} // namespace pf

#include "src/utils/hash.inl"

#endif // _PF_UTILS_HASH_hpp_