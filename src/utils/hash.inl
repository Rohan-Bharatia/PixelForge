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

#ifndef _PF_UTILS_HASH_inl_
#define _PF_UTILS_HASH_inl_

// std
#include <string_view>
#include <array>

#include "include/utils/hash.hpp"
#include "include/utils/prerequisites.h"

namespace pf
{
    namespace Detail
    {
        constexpr auto generate_CRC_table(uint32 polynomial = 0xedB88320)
		{
            PF_WARNING_PUSH()
            PF_WARNING_MSVC_DISABLE(4146)

			constexpr uint32 bc = 256;
			constexpr uint32 iter_count = 8;

			std::array<uint32, bc> crc32_table{};

			for(uint32 byte = 0u; byte < bc; byte++)
			{
				uint32 crc = byte;

				for(uint32 i = 0; i < iter_count; i++)
				{
					uint32 mask = (-(crc & 1));
					crc = (crc >> 1) ^ (polynomial & mask);
				}

				crc32_table[byte] = crc;
			}

			return crc32_table;

            PF_WARNING_POP()
		}

        static constexpr auto crc32_table = generate_CRC_table();
		static_assert(crc32_table.size() == 256 && crc32_table[1] == 0x77073096 && crc32_table[255] == 0x2D02EF8D,
                      "\'generate_CRC32_table(T = 0xedB88320)\' generated unexpected result!");

		template<typename T>
        constexpr T FNV1_offset_basis = static_cast<T>(0xcbf29ce484222325ull);
		template<typename T>
        constexpr T FNV1_prime = static_cast<T>(0x100000001b3ull);
    } // namespace Detail
    
    template<typename T>
    void hash_combine(size_t& seed, const T& v)
    {
        constexpr uint64 k = 0x9ddfea08eb382d69ULL;

		std::hash<T> hasher;
		uint64 a = (hasher(v) ^ seed) * k;
		a ^= (a >> 47);

		uint64 b = (seed ^ a) * k;
		b ^= (b >> 47);

		seed = static_cast<size_t>(b * k);
    }

	template<typename T, typename... Args>
    size_t hash_combine(const T& v, const Args&... args)
    {
        size_t hash = std::hash<T>{}(v);

		if constexpr(sizeof...(Args) > 0)
			hash_combine(hash, hash_combine(args...));

		return hash;
    }

    template<typename T>
	template<typename... Args>
	size_t HashFunctor<T>::operator () (Args&&... args)
	{
		return static_cast<size_t>(T{}(std::forward<Args>(args)...));
	}

    template<typename T>
    constexpr T CRC(const char* str) noexcept
	{
		T crc = 0xFFFFFFFFu;

		for(size_t i = 0u; str[i]; i++)
			crc = Detail::crc32_table[(crc ^ str[i]) & 0xFF] ^ (crc >> 8);

		return ~crc;
	}

    template<typename T>
	constexpr T CRC(std::string_view str) noexcept
	{
		T crc = 0xFFFFFFFFu;

		for(size_t i = 0u; i < str.size(); i++)
			crc = Detail::crc32_table[(crc ^ str[i]) & 0xFF] ^ (crc >> 8);

		return ~crc;
	}

	template<typename T>
    constexpr T CRC(const uint8* input, size_t size) noexcept
	{
		T crc = 0xFFFFFFFFu;

		for(size_t i = 0u; i < size; i++)
			crc = Detail::crc32_table[(crc ^ input[i]) & 0xFF] ^ (crc >> 8);

		return ~crc;
	}

	template<typename T, size_t N>
	constexpr T CRC32(const char(&str)[N]) noexcept
	{
		return CRC<T>(std::string_view(str, N));
	}

    template<typename T>
    template<typename... Args>
	T CRCHash::operator () (Args&&... args)
	{
		return CRC<T>(std::forward<Args>(args)...);
	}

    template<typename T>
	constexpr T FNV1a(const char* str) noexcept
	{
		T hash = Detail::FNV1_offset_basis<T>;

		for(size_t i = 0u; str[i]; i++)
		{
			hash ^= T(str[i]);
			hash *= Detail::FNV1_prime<T>;
		}

		return hash;
	}
    
    template<typename T>
	constexpr T FNV1a(std::string_view str) noexcept
	{
		T hash = Detail::FNV1_offset_basis<T>;

		for(size_t i = 0u; i < str.size(); i++)
		{
			hash ^= T(str[i]);
			hash *= Detail::FNV1_prime<T>>;
		}

		return hash;
	}

    template<typename T>
	constexpr T FNV1a(const uint8* data, size_t size) noexcept
	{
		T hash = Detail::FNV1_offset_basis<T>;

		for(size_t i = 0u; i < size; i++)
		{
			hash ^= data[i];
			hash *= Detail::FNV1_prime<T>;
		}

		return hash;
	}

	template<typename T, size_t N>
	constexpr T FNV1a(const char(&str)[N]) noexcept
	{
		return FNV1a<32>(std::string_view(str, N));
	}

	template<typename T>
    template<typename... Args>
	T FNV1aHash<T>::operator () (Args&&... args)
	{
		return FNV1a<T>(std::forward<Args>(args)...);
	}
} // namespace pf

#endif // _PF_UTILS_HASH_inl_