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

#ifndef _PF_UTILS_FLAGS_hpp_
#define _PF_UTILS_FLAGS_hpp_

// std
#include <iterator>
#include <type_traits>

#include "prerequisites.h"
#include "math-utils.hpp"
#include "type-traits.h"

namespace pf
{
    template<typename E>
	struct EnumAsFlags;

    constexpr bool enable_enum_as_flags = false;
    constexpr bool enable_auto_flag_for_flags = true;

    template<typename T, typename = void>
	struct IsEnumFlag : std::bool_constant<IsComplete_v<EnumAsFlags<T>>>
    {};

	template<typename T>
	struct IsEnumFlag<T, std::void_t<std::enable_if_t<enable_auto_flag_for_flags>>> : std::true_type
    {};

	template<typename E, typename = void>
	struct GetEnumAutoFlag : std::bool_constant<enable_auto_flag_for_flags(E{})>
    {};

	template<typename E>
	struct GetEnumAutoFlag<E, std::void_t<decltype(E::auto_flag)>> : std::bool_constant<E::auto_flag>
    {};

	template<typename E, typename = void>
	struct GetEnumFlagMax
	{
		static constexpr size_t max = EnumValueCount<E>::value - 1;
	};

	template<typename E>
	struct GetEnumFlagMax<E, std::void_t<decltype(EnumAsFlags<E>::max)>>
	{
		static constexpr size_t max = static_cast<size_t>(EnumAsFlags<E>::max);
	};

    template<typename E>
    class Flags
    {
        static_assert(std::is_enum_v<E>, "Type must be an enumeration!");
        static_assert(IsEnumFlag<E>(), "Enum has not been enabled as flags by an EnumAsFlags specialization nor enable_enum_as_flags ADL variable!");

        static constexpr size_t max_value = GetEnumFlagMax<E>::max;
        static constexpr bool auto_flag = GetEnumAutoFlag<E>();

        using bitfield16 = std::conditional_t<(max_value >= 8), uint16, uint8>;
        using bitfield32 = std::conditional_t<(max_value >= 16), uint32, bitfield16>;

    public:
        class iterator;
		friend iterator;

		using bitfield = std::conditional_t<(Max_value >= 32), uint64, bitfield32>;

        constexpr Flags(bitfield value = 0);
		constexpr Flags(E enum_val);

		constexpr void clear();
		constexpr void clear(const Flags& flags);
		size_t count() const;

		constexpr void set(const Flags& flags);

		constexpr bool test(const Flags& flags) const;

		constexpr iterator begin() const;
		constexpr iterator end() const;
		size_t size() const;

        explicit constexpr operator bool () const;
		template<typename T, typename = std::enable_if_t<std::is_integral<T>::value && sizeof(T) >= sizeof(bitfield)>>
        explicit constexpr operator T () const;

		constexpr Flags operator ~ () const;
		constexpr Flags operator & (const Flags& rhs) const;
		constexpr Flags operator | (const Flags& rhs) const;
		constexpr Flags operator ^ (const Flags& rhs) const;

		constexpr bool operator == (const Flags& rhs) const;
		constexpr bool operator != (const Flags& rhs) const;

		constexpr Flags& operator |= (const Flags& rhs);
		constexpr Flags& operator &= (const Flags& rhs);
		constexpr Flags& operator ^= (const Flags& rhs);

        static constexpr bitfield get_flag_value(E enum_val);

		static constexpr bitfield value_mask = static_cast<bitfield>((uint64(1) << (max_value + 1)) - 1);

	private:
		bitfield m_value;
    };

    template<typename T>
	class Flags<T>::iterator
	{
		friend Flags;

	public:
		using iterator_category = std::input_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;

		iterator(const iterator&) = default;
		iterator(iterator&&) = default;

		iterator& operator = (const iterator&) = default;
		iterator& operator = (iterator&&) = default;

		iterator operator ++ (int);
		iterator& operator ++ ();

		constexpr bool operator == (const iterator& rhs) const;
		constexpr bool operator != (const iterator& rhs) const;
		value_type operator * () const;

	private:
		constexpr iterator(bitfield remaining_flags);

		bitfield m_remaining_flags;
	};

    template<typename E>
    constexpr Flags<E> operator & (E lhs, Flags<E> rhs);
	template<typename E>
    constexpr Flags<E> operator | (E lhs, Flags<E> rhs);
	template<typename E>
    constexpr Flags<E> operator ^ (E lhs, Flags<E> rhs);

    namespace FlagsOperators
	{
		template<typename E>
        constexpr std::enable_if_t<IsEnumFlag<E>::value, Flags<E>> operator ~ (E lhs);
		template<typename E>
        constexpr std::enable_if_t<IsEnumFlag<E>::value, Flags<E>> operator & (E lhs, E rhs);
		template<typename E>
        constexpr std::enable_if_t<IsEnumFlag<E>::value, Flags<E>> operator | (E lhs, E rhs);
		template<typename E>
        constexpr std::enable_if_t<IsEnumFlag<E>::value, Flags<E>> operator ^ (E lhs, E rhs);
	} // namespace FlagsOperators

	using namespace FlagsOperators;
} // namespace pf

using namespace pf::FlagsOperators;

namespace std
{
	template<typename E>
	struct hash<pf::Flags<E>>
	{
		size_t operator () (const pf::Flags<E>& flags);
	};
} // namespace std


#include "src/utils/flags.inl"

#endif // _PF_UTILS_FLAGS_hpp_