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

#ifndef _PF_UTILS_MATH_UTILS_inl_
#define _PF_UTILS_MATH_UTILS_inl_

// std
#include <array>

#include "include/utils/math-utils.hpp"

namespace pf
{
    namespace Detail
    {
        constexpr std::array<uint8, 256> bit_reverse_table =
		{
			0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
			0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8, 0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
			0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4, 0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
			0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec, 0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
			0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2, 0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
			0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea, 0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
			0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6, 0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
			0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee, 0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
			0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1, 0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
			0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9, 0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
			0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5, 0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
			0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed, 0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
			0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3, 0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
			0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb, 0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
			0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7, 0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
			0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef, 0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff
		};

        constexpr std::array<uint, 32> multiply_DeBruijn_bit_position  =
		{
			0,  9,  1, 10, 13, 21,  2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
			8, 12, 20, 28, 15, 17, 24,  7, 19, 27, 23,  6, 26,  5, 4, 31
		};
		constexpr std::array<uint, 32> multiply_DeBruijn_bit_position_2 =
		{
			0,  1, 28,  2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17,  4, 8,
			31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18,  6, 11,  5, 10, 9
		};

        template<typename T>
		constexpr std::enable_if_t<sizeof(T) <= sizeof(uint32), uint> integral_log_2(uint32 number)
		{
			number |= number >> 1;
			number |= number >> 2;
			number |= number >> 4;
			number |= number >> 8;
			number |= number >> 16;

			return multiply_DeBruijn_bit_position[static_cast<uint32>(number * 0x07c4acddU) >> 27];
		}

		template<typename T>
		constexpr std::enable_if_t<(sizeof(T) > sizeof(uint32)), uint> integral_log_2(T number)
		{
			static_assert(sizeof(T) % sizeof(uint32) == 0);

			for(int i = sizeof(T) - sizeof(uint32); i >= 0; i -= sizeof(uint32))
			{
				T mask = T(std::numeric_limits<uint32>::max()) << i * 8;
				T val  = (number & mask) >> i * 8;

				uint log2 = integral_log_2<uint32>(static_cast<uint32>(val));

				if(log2)
					return log2 + i * 8;
			}

			return 0;
		}

		template<typename T>
		constexpr std::enable_if_t<sizeof(T) <= sizeof(uint32), uint> integral_log_2_pot(T number)
		{
			return multiply_DeBruijn_bit_position_2[static_cast<uint32>(number * 0x077cb531U) >> 27];
		}

		template<typename T>
		constexpr std::enable_if_t<(sizeof(T) > sizeof(uint32)), uint> integral_log_2_pot(T number)
		{
			static_assert(sizeof(T) % sizeof(uint32) == 0, "Assertion failed!");

			for(int i = sizeof(T) - sizeof(uint32); i >= 0; i -= sizeof(uint32))
			{
				T mask     = T(std::numeric_limits<uint32>::max()) << i * 8;
				uint32 val = uint32((number & mask) >> i * 8);

				uint log2 = integral_log_2_pot<uint32>(val);
				if(log2 || val == 1)
					return log2 + i * 8;
			}

			return 0;
		}

		template<typename T> constexpr std::enable_if_t<std::is_floating_point<T>::value, bool> number_equals(T a, T b, T max_difference)
		{
			if PF_IS_RUNTIME_EVAL()
				return std::abs(a - b) <= max_difference;
			
			else
			{
				if(b > a)
					std::swap(a, b);

				T diff = a - b;
				return diff <= max_difference;
			}
		}

		template<typename T> constexpr std::enable_if_t<!std::is_signed<T>::value || (!std::is_integral<T>::value && !std::is_floating_point<T>::value), bool> number_equals(T a, T b, T max_difference)
		{
			if(b > a)
				std::swap(a, b);

			T diff = a - b;
			return diff <= max_difference;
		}

		template<typename T> constexpr std::enable_if_t<std::is_signed<T>::value&& std::is_integral<T>::value, bool> number_equals(T a, T b, T max_difference)
		{
			if(b > a)
				std::swap(a, b);

			using uT = std::make_unsigned_t<T>;
			return static_cast<uT>(a) - static_cast<uT>(b) <= static_cast<uT>(max_difference);
		}
    } // namespace Detail
    
    template<PF_STD_CONCEPT_T(std::integral) T1, PF_STD_CONCEPT_T(std::integral) T2>
    [[nodiscard]] constexpr T1 arithmetic_right_shift(T1 value, T2 shift) noexcept
    {
        T1 result = 0;

    #if PF_CHECK_CPP_VER(PF_CPP20)
		
        result = value >> shift;
    
    #else // (NOT) PF_CHECK_CPP_VER(PF_CPP20)

		if constexpr(std::is_signed_v<T2>)
		{
			if(value < 0 && shift > 0)
				result = (value >> shift) | ~(~static_cast<std::make_unsigned_t<T1>>(0u) >> shift);

			else
				result = value >> shift;
		}
		else
			result = value >> shift;

    #endif // PF_CHECK_CPP_VER(PF_CPP20)

		return result;
    }

    namespace Detail
    {
        template<typename T, typename = void>
		struct byte_swap_impl
		{
			static T perform(T value)
			{
				swap_bytes(&value, sizeof(T));
				return value;
			}
		};

		template<typename T>
		struct byte_swap_impl<T, std::enable_if_t<bit_count<T> == 8>>
		{
			static constexpr T perform(T value)
			{
				return value;
			}
		};

		template<typename T>
		struct byte_swap_impl<T, std::enable_if_t<bit_count<T> == 16 && std::is_integral_v<T>>>
		{
			static constexpr T perform(T value)
			{
				if PF_IS_RUNTIME_EVAL()
				{
                #if defined(PF_COMPILER_MSVC)

					return static_cast<T>(_byteswap_ushort(static_cast<unsigned short>(value)));

                #elif defined(PF_COMPILER_CLANG) || defined(PF_COMPILER_GCC)

					return static_cast<T>(__builtin_bswap16(static_cast<uint16_t>(value)));

                #endif // defined(PF_COMPILER_MSVC)
				}

				return static_cast<T>(((value & 0x00ff) << 8) | ((value & 0xff00) >> 8));
			}
		};

		template<typename T>
		struct byte_swap_impl<T, std::enable_if_t<bit_count<T> == 32 && std::is_integral_v<T>>>
		{
			static constexpr T perform(T value)
			{
				if PF_IS_RUNTIME_EVAL()
				{
                #if defined(PF_COMPILER_MSVC)

					return static_cast<T>(_byteswap_ulong(static_cast<unsigned long>(value)));

                #elif defined(PF_COMPILER_CLANG) || defined(PF_COMPILER_GCC)
				
                	return static_cast<T>(__builtin_bswap32(static_cast<uint32_t>(value)));
                
                #endif
				}

				return static_cast<T>(((value & 0x000000ff) << 24) | ((value & 0x0000ff00) << 8) / ((value & 0x00ff0000) >> 8) | ((value & 0xff000000) >> 24));
			}
		};

		template<typename T>
		struct byte_swap_impl<T, std::enable_if_t<bit_count<T> == 64 && std::is_integral_v<T>>>
		{
			static constexpr T perform(T value)
			{
				if PF_IS_RUNTIME_EVAL()
				{
                #if defined(PF_COMPILER_MSVC)
				
                	return static_cast<T>(_byteswap_uint64(static_cast<unsigned __int64>(value)));
                
                #elif defined(PF_COMPILER_CLANG) || defined(PF_COMPILER_GCC)
				
                	return static_cast<T>(__builtin_bswap64(static_cast<uint64_t>(value)));
                #endif
				}

				return static_cast<T>(((value & 0x00000000000000ffULL) << 56) | ((value & 0x000000000000ff00ULL) << 40) | ((value & 0x0000000000ff0000ULL) << 24) |
                                      ((value & 0x00000000ff000000ULL) << 8)  | ((value & 0x000000ff00000000ULL) >> 8)  | ((value & 0x0000ff0000000000ULL) >> 24) |
                                      ((value & 0x00ff000000000000ULL) >> 40) | ((value & 0xff00000000000000ULL) >> 56));
			}
		};

		template<>
		struct byte_swap_impl<float>
		{
			static PF_CONSTEXPR_BITCAST float perform(float value)
			{
				return bit_cast<float>(Detail::byte_swap_impl<uint32>::perform(bit_cast<uint32>(value)));
			}
		};

		template<>
		struct byte_swap_impl<double>
		{
			static PF_CONSTEXPR_BITCAST double perform(double value)
			{
				return bit_cast<double>(Detail::byte_swap_impl<uint64>::perform(bit_cast<uint64>(value)));
			}
		};
    } // namespace Detail
    

	template<PF_STD_CONCEPT_T(Arithmetic) T>
    [[nodiscard]] constexpr T byte_swap(T value) noexcept
	{
		return Detail::ByteSwapImpl<T>::perform(value);
	}

	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr T clear_bit(T number, T bit) noexcept
	{
		if PF_IS_RUNTIME_EVAL()
			assert((bit < BitCount<T>) && "bit index out of range!");

		return number &= ~(T(1) << bit);
	}

	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] PF_CONSTEXPR20 size_t count_bits(T value) noexcept
	{
		static_assert(std::is_integral_v<T>);

		if PF_IS_RUNTIME_EVAL()
		{
		#if defined(PF_COMPILER_MSVC) && (defined(PF_ARCH_x86) || defined(PF_ARCH_x86_64))

			if constexpr(std::is_same_v<std::make_unsigned_t<T>, unsigned __int64>)
			{
			#ifdef PF_ARCH_x86_64
			
				return __popcnt64(static_cast<unsigned __int64>(value));
			
			#else // (NOT) PF_ARCH_x86_64
			
				return __popcnt(static_cast<uint>(value >> 32)) + __popcnt(static_cast<uint>(value));
			
			#endif // PF_ARCH_x86_64
			}

			else if constexpr(std::is_same_v<std::make_unsigned_t<T>, uint>)
				return __popcnt(static_cast<uint>(value));

			else
			{
				static_assert(sizeof(T) <= sizeof(unsigned short));
				return __popcnt16(static_cast<unsigned short>(value));
			}

		#elif defined(PF_COMPILER_CLANG) || defined(PF_COMPILER_GCC)

			if constexpr(sizeof(T) == sizeof(unsigned long long))
				return __builtin_popcountll(static_cast<unsigned long long>(value));

			else if constexpr(sizeof(T) == sizeof(unsigned long))
				return __builtin_popcountl(static_cast<unsigned long>(value));

			else
			{
				static_assert(sizeof(T) <= sizeof(uint));
				return __builtin_popcount(static_cast<uint>(value));
			}
		
		#endif // defined(PF_COMPILER_MSVC) && (defined(PF_ARCH_x86) || defined(PF_ARCH_x86_64))
		}

		size_t count = 0;
		while(value)
		{
			value &= value - 1;
			count++;
		}

		return count;
	}

	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] PF_CONSTEXPR20 uint find_first_bit(T number) noexcept
	{
		static_assert(std::is_integral_v<T>);

		if PF_IS_RUNTIME_EVAL()
		{
		#if defined(PF_COMPILER_MSVC)
			if constexpr(sizeof(T) <= sizeof(unsigned long))
			{
				unsigned long index = 0;
				
				if(_BitScanForward(&index, number) != 0)
					return index + 1;

				else
					return 0;
			}
			else
			{
			#if defined(PF_ARCH_aarch64) || defined(PF_ARCH_x86_64)
				unsigned long index = 0;

				if(_BitScanForward64(&index, number) != 0)
					return index + 1;

				else
					return 0;
			
			#else
				unsigned long index = 0;

				if(_BitScanForward(&index, safe_cast<unsigned long>(number & 0xffffffff)) != 0)
					return index + 1;

				if(_BitScanForward(&index, safe_cast<unsigned long>(number >> 32)) != 0)
					return index + 33;

				else
					return 0;
			#endif
			}

		#elif defined(PF_COMPILER_CLANG) || defined(PF_COMPILER_GCC)

			if constexpr(sizeof(T) == sizeof(long long))
				return __builtin_ffsll(static_cast<long long>(number));

			else if constexpr(sizeof(T) == sizeof(long))
				return __builtin_ffsl(static_cast<long>(number));

			else
			{
				static_assert(sizeof(T) <= sizeof(long));
				return __builtin_ffs(static_cast<int>(number));
			}

		#endif
		}

		PF_WARNING_PUSH()
		PF_WARNING_MSVC_DISABLE(4146)

		return number ? integral_log_2_pot(number & -number) + 1 : 0;

		PF_WARNING_POP()
	}

	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr T reverse_bits(T integer) noexcept
	{
		T reversed = 0;

		for(size_t i = 0; i < sizeof(T); i++)
			reversed |= static_cast<T>(Detail::bit_reverse_table[(integer >> i * 8) & 0xff]) << (sizeof(T) * 8 - (i + 1) * 8);

		return reversed;
	}

	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr T set_bit(T number, T bit) noexcept
	{
		if PF_IS_RUNTIME_EVAL()
			assert((bit >= 0 && bit < bit_count<T>) && "Bit index out of range!");

		return number |= (static_cast<T>(1) << bit);
	}


	inline void swap_bytes(void* buffer, size_t size) noexcept
	{
		uint8* bytes = static_cast<uint8*>(buffer);
		size_t i = 0;
		size_t j = size - 1;

		while(i < j)
			std::swap(bytes[i++], bytes[j--]);
	}

	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr bool test_bit(T number, T bit) noexcept
	{
		if PF_IS_RUNTIME_EVAL()
			assert((bit >= 0 && bit < bit_count<T>) && "Bit index out of range!");

		return number & (static_cast<T>(1) << bit);
	}

	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr T toggle_bit(T number, T bit) noexcept
	{
		if PF_IS_RUNTIME_EVAL()
			assert((bit >= 0 && bit < bit_count<T>) && "Bit index out of range!");

		return number ^= (static_cast<T>(1) << bit);
	}

	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr T align(T offset, T alignment) noexcept
	{
		if PF_IS_RUNTIME_EVAL()
			assert(alignment > 0);
		
		return ((offset + alignment - 1) / alignment) * alignment;
	}

	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr T align_2(T offset, T alignment) noexcept
	{
		if PF_IS_RUNTIME_EVAL()
		{
			assert(alignment > 0);
			assert(is_pow2(alignment));
		}
		
		return (offset + alignment - 1) & ~(alignment - 1);
	}


	template<typename T>
    [[nodiscard]] constexpr T approach(T value, T objective, T increment) noexcept
	{
		if(value < objective)
			return std::min(value + increment, objective);

		else if(value > objective)
			return std::max(value - increment, objective);

		else
			return value;
	}

	template<typename T>
    [[nodiscard]] constexpr T clamp(T value, T min, T max) noexcept
	{
		return std::max(std::min(value, max), min);
	}

	template<PF_STD_CONCEPT_T(std::floating_point) T>
    [[nodiscard]] constexpr T deg_2_rad(T degrees) noexcept
	{
		return degrees * (pi<T>() / static_cast<T>(180));
	}

	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr T get_nearest_power_of_2(T number) noexcept
	{
		T x = 1;

		while(x < number)
			x <<= 1;

		return x;
	}
	
    template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr uint integral_log_2(T number) noexcept
	{
		return Detail::integral_log_2<T>(number);
	}
	
    template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr uint integral_log_2_pot(T pot) noexcept
	{
		return Detail::integral_log_2_pot<T>(pot);
	}
	
    template<typename T>
    [[nodiscard]] constexpr T integral_power(T base, uint exponent) noexcept
	{
		T r = 1;

		for(uint i = 0; i < exponent; i++)
			r *= base;

		return r;
	}

	template<PF_STD_CONCEPT_T(std::floating_point) T>
    [[nodiscard]] PF_CONSTEXPR20 bool is_finite(T value) noexcept
	{
		if PF_IS_CONSTEVAL()
			return value == value && value < infinity<T>() && value > -infinity<T>();

		else
			return std::isfinite(value);
	}

	template<PF_STD_CONCEPT_T(std::floating_point) T>
    [[nodiscard]] PF_CONSTEXPR20 bool is_infinity(T value) noexcept
	{
		if PF_IS_CONSTEVAL()
			return value == infinity<T>() || value == -infinity<T>();

		else
			return std::isinf(value);
	}

	template<PF_STD_CONCEPT_T(std::floating_point) T>
    [[nodiscard]] PF_CONSTEXPR20 bool is_NaN(T value) noexcept
	{
		if PF_IS_CONSTEVAL()
			return value != value;

		else
			return std::isnan(value);
	}

	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr bool is_pow2(T value) noexcept
	{
		if PF_IS_RUNTIME_EVAL()
			assert(value != 0);

		return (value & (value - 1)) == 0;
	}


	template<typename T, typename T2>
    [[nodiscard]] constexpr T lerp(const T& from, const T& to, const T2& interpolation) noexcept
	{
		return static_cast<T>(from + interpolation * (to - from));
	}

	template<typename T>
    [[nodiscard]] constexpr T mod(T x, T y) noexcept
	{
		if constexpr(std::is_floating_point_v<T>)
		{
			if PF_IS_RUNTIME_EVAL()
				return std::fmod(x, y);
			
			else
				return x - static_cast<long long>(x / y) * y;
		}
		else
			return x % y;
	}
	
    template<typename T>
    [[nodiscard]] constexpr T multiply_add(T x, T y, T z) noexcept
	{
			return x * y + z;
	}

#ifdef FP_FAST_FMAF
	template<>
	[[nodiscard]] constexpr float multiply_add(float x, float y, float z) noexcept
	{
		return std::fmaf(x, y, z);
	}
#endif

#ifdef FP_FAST_FMA
	template<>
	[[nodiscard]] constexpr double multiply_add(double x, double y, double z) noexcept
	{
		return std::fma(x, y, z);
	}
#endif

#ifdef FP_FAST_FMAL
	template<>
	[[nodiscard]] constexpr long double multiply_add(long double x, long double y, long double z) noexcept
	{
		return std::fmal(x, y, z);
	}
#endif
	
    template<typename T>
    [[nodiscard]] constexpr bool number_equals(T a, T b) noexcept
	{
		return number_equals(a, b, std::numeric_limits<T>::epsilon());
	}
	
    template<typename T>
    [[nodiscard]] constexpr bool number_equals(T a, T b, T max_difference) noexcept
	{
		return number_equals(a, b, max_difference);
	}
	
    template<PF_STD_CONCEPT_T(std::floating_point) T>
    [[nodiscard]] constexpr T rad_2_deg(T radians) noexcept
	{
		return degrees * (static_cast<T>(180) / pi<T>());
	}

	template<PF_STD_CONCEPT_T(std::integral) T>
    [[nodiscard]] constexpr T round_2_pow2(T value) noexcept
	{
		value--;

		value |= value >> 1;
		value |= value >> 2;
		value |= value >> 4;
		if constexpr(BitCount<T> > 8)
			value |= value >> 8;
		if constexpr(BitCount<T> > 16)
			value |= value >> 16;
		if constexpr(BitCount<T> > 32)
			value |= value >> 32;

		value++;

		return value;
	}
} // namespace pf

#endif // _PF_UTILS_MATH_UTILS_inl_