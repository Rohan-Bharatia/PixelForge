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

#ifndef _PF_UTILS_ALGORITHM_inl_
#define _PF_UTILS_ALGORITHM_inl_

// std
#include <cassert>
#include <type_traits>
#include <memory>

#include "include/utils/algorithm.hpp"
#include "include/utils/prerequisites.h"

#ifdef PF_HAS_CONSTEXPR_BITCAST_STD

#include <bit>

#elif !defined(PF_HAS_CONSTEXPR_BITCAST_BUILTIN)

#include <cstring>

#endif // PF_HAS_CONSTEXPR_BITCAST_STD

#ifdef PF_COMPILER_MSVC

#pragma intrinsic(_BitScanForward)

#if defined(PF_ARCH_aarch64) || defined(PF_ARCH_x86_64)

#pragma intrinsic(_BitScanForward64)

#endif // defined(PF_ARCH_aarch64) || defined(PF_ARCH_x86_64)

#if defined(PF_ARCH_x86) || defined(PF_ARCH_x86_64)

#include <intrin.h>

#endif // defined(PF_ARCH_x86) || defined(PF_ARCH_x86_64)

#endif // PF_COMPILER_MSVC

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
    namespace Detail
    {
        template<typename From>
		class safe_caster
		{
			static_assert(std::is_reference_v<From>);

			public:
				template<typename T>
				safe_caster(T&& from) : m_from(std::forward<T>(from))
				{}

				template<typename To>
				operator To() const
				{
					return safe_cast<To>(m_from);
				}

			private:
				From m_from;
		};
    } // namespace Detail
    
    template<typename T>
    decltype(auto) access_by_offset(void* base_ptr, size_t offset) noexcept
    {
        if constexpr(std::is_lvalue_reference_v<T>)
			return *reinterpret_cast<std::remove_reference_t<T>*>(static_cast<uint8*>(base_ptr) + offset);

		else if constexpr(std::is_pointer_v<T>)
			return reinterpret_cast<T>(static_cast<uint8*>(base_ptr) + offset);

		else
			static_assert(AlwaysFalse<T>(), "\'access_by_offset<T>(void*, size_t)\' requires a reference or pointer type!");
    }

	template<typename T>
    decltype(auto) access_by_offset(const void* base_ptr, size_t offset) noexcept
    {
        static_assert(std::is_lvalue_reference_v<T> || std::is_pointer_v<T>);

		if constexpr(std::is_lvalue_reference_v<T>)
			return *reinterpret_cast<std::remove_reference_t<T>*>(static_cast<const uint8*>(base_ptr) + offset);

		else if constexpr(std::is_pointer_v<T>)
			return reinterpret_cast<T>(static_cast<const uint8*>(base_ptr) + offset);
            
		else
			static_assert(AlwaysFalse<T>(), "\'access_by_offset<T>(const void*, size_t)\' requires a reference or pointer type!");
    }

	template<typename To, typename From>
    PF_CONSTEXPR_BITCAST To bit_cast(const From& value) noexcept
    {
        static_assert(sizeof(To) == sizeof(From));
		static_assert(std::is_trivially_copyable_v<From>);
		static_assert(std::is_trivially_copyable_v<To>);

    #ifdef PF_HAS_CONSTEXPR_BITCAST_STD

		return std::bit_cast<To>(value);

    #elif defined(PF_HAS_CONSTEXPR_BITCAST_BUILTIN)

		return __builtin_bit_cast(To, value);

    #else // (NOT) PF_HAS_CONSTEXPR_BITCAST_STD, defined(PF_HAS_CONSTEXPR_BITCAST_BUILTIN)

		To result;
		std::memcpy(&result, &value, sizeof(To));

		return result;
        
#endif // PF_HAS_CONSTEXPR_BITCAST_STD
    }

	template<typename T, size_t N>
    constexpr size_t count_of(T(&name)[N]) noexcept
    {
        return N;
    }

	template<typename T> [[nodiscard]]
    constexpr size_t count_of(const T& c) noexcept
    {
        return c.size();
    }

	template<typename P, typename T>
    PF_CONSTEXPR_BITCAST P int_2_ptr(T integer) noexcept
    {
        static_assert(std::is_pointer_v<P>);
		static_assert(sizeof(T) == sizeof(P), "integer type must match pointer size!");

		return bit_cast<P>(safe_cast<uintptr_t>(integer));
    }

	template<typename T, typename P>
    PF_CONSTEXPR_BITCAST T ptr_2_int(P* ptr) noexcept
    {
        static_assert(sizeof(T) == sizeof(P*), "integer type must match pointer size!");

		return safe_cast<T>(bit_cast<uintptr_t>(ptr));
    }

	template<typename M, typename T>
    auto& retrieve(M& map, const T& key) noexcept
    {
        auto it = map.find(key);
		assert(it != map.end());

		return it->second;
    }

	template<typename M, typename T>
    const auto& retrieve(const M& map, const T& key) noexcept
    {
        auto it = map.find(key);
		assert(it != map.end());

		return it->second;
    }

	template<typename To, typename From>
    To safe_cast(From&& value) noexcept
    {
        PF_WARNING_PUSH()
        PF_WARNING_MSVC_DISABLE(4702)

    #if defined(PF_DEBUG) && !defined(NDEBUG)

        if constexpr(std::is_integral_v<To>)
        {
            if constexpr(std::is_enum_v<From>)
                return safe_cast<To>(static_cast<std::underlying_type_t<From>>(value));
            
            else if constexpr(std::is_floating_point_v<From>)
            {
                assert(std::floor(value) == value);

                assert(value <= static_cast<From>(std::numeric_limits<To>::max()));
                assert(value >= static_cast<From>(std::numeric_limits<To>::lowest()));
            }
            else if constexpr(std::is_integral_v<From>)
            {
                using max_value_type = std::conditional_t<((!std::is_signed_v<From> && std::is_signed_v<To>) || (std::is_signed_v<From> == std::is_signed_v<To> && sizeof(From) > sizeof(To))), From, To>;
                using min_value_type = std::conditional_t<((std::is_signed_v<From> && !std::is_signed_v<To>) || (std::is_signed_v<From> == std::is_signed_v<To> && sizeof(From) > sizeof(To))), From, To>;

                if constexpr(!std::is_signed_v<To>)
                    assert(value >= 0);

                assert(static_cast<max_value_type>(value) <= static_cast<max_value_type>(std::numeric_limits<To>::max()));
                assert(static_cast<min_value_type>(value) >= static_cast<min_value_type>(std::numeric_limits<To>::lowest()));
            }
        }

        else if constexpr(std::is_enum_v<To>)
            return static_cast<To>(SafeCast<std::underlying_type_t<To>>(value));
        
        else if constexpr(std::is_floating_point_v<To>)
        {
            if constexpr(std::is_floating_point_v<From>)
            {
                using max_value_type = std::conditional_t<(sizeof(From) > sizeof(To)), From, To>;
                using min_value_type = std::conditional_t<(sizeof(From) > sizeof(To)), From, To>;

                assert(static_cast<max_value_type>(value) <= static_cast<max_value_type>(std::numeric_limits<To>::max()));
                assert(static_cast<min_value_type>(value) >= static_cast<min_value_type>(std::numeric_limits<To>::lowest()));
            }
        }

        else if constexpr(std::is_reference_v<To>)
        {
            if constexpr(std::is_reference_v<From>)
            {
                using base_from_type = std::remove_reference_t<std::remove_cv_t<From>>;
                using base_to_type = std::remove_reference_t<std::remove_cv_t<To>>;

                if constexpr(!std::is_same_v<base_from_type, base_to_type> && std::is_base_of_v<From, To> && std::is_polymorphic_v<From>)
                {
                    using to_ptr = std::add_pointer_t<std::remove_reference_t<To>>;
                    assert(dynamic_cast<to_ptr>(&value) != nullptr);
                }
            }
        }

        else if constexpr(std::is_pointer_v<To>)
        {
            if constexpr(std::is_pointer_v<From>)
            {
                using base_from_type = std::remove_pointer_t<std::remove_cv_t<From>>;
                using base_to_type = std::remove_pointer_t<std::remove_cv_t<To>>;

                if constexpr(!std::is_same_v<base_from_type, base_to_type> && std::is_base_of_v<From, To> && std::is_polymorphic_v<From>)
                    assert(!value || dynamic_cast<To>(value) != nullptr);
            }
        }

    #endif // defined(PF_DEBUG) && !defined(NDEBUG)

	    return static_cast<To>(value);

        PF_WARNING_POP()
    }

	template<typename From> [[nodiscard]]
    auto safe_caster(From&& value) noexcept
    {
        return Detail::safe_caster<decltype(value)>(std::forward<From>(value));
    }

	template<typename T, typename U>
    std::unique_ptr<T> static_unique_ptr_cast(std::unique_ptr<U>&& ptr) noexcept
    {
        return std::unique_ptr<T>(safe_cast<T*>(ptr.release()));
    }

	template<typename T> [[nodiscard]]
    constexpr auto underlying_cast(T value) noexcept -> std::underlying_type_t<T>
    {
        return static_cast<std::underlying_type_t<T>>(value);
    }
} // namespace pf

#endif // _PF_UTILS_ALGORITHM_inl_