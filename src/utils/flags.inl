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

#ifndef _PF_UTILS_FLAGS_inl_
#define _PF_UTILS_FLAGS_inl_

// std
#include <functional>

#include "include/utils/flags.hpp"

namespace pf
{
    template<typename E>
	constexpr Flags<E>::Flags(bitfield value) : m_value(value)
	{}

	template<typename E>
	constexpr Flags<E>::Flags(E enum_val) : Flags(get_flag_value(enum_val))
	{}

	template<typename E>
	constexpr void Flags<E>::clear()
	{
		m_value = 0;
	}

	template<typename E>
	constexpr void Flags<E>::clear(const Flags& flags)
	{
		m_value &= ~flags.m_value;
	}

	template<typename E>
	size_t Flags<E>::count() const
	{
		return count_bits(m_value);
	}

	template<typename E>
	constexpr void Flags<E>::set(const Flags& flags)
	{
		m_value |= flags.m_value;
	}

	template<typename E>
	constexpr bool Flags<E>::test(const Flags& flags) const
	{
		return (m_value & flags.m_value) == flags.m_value;
	}

	template<typename E>
	constexpr auto Flags<E>::begin() const -> iterator
	{
		return iterator{ m_value };
	}

	template<typename E>
	constexpr auto Flags<E>::end() const -> iterator
	{
		return iterator{ 0 };
	}

	template<typename E>
	size_t Flags<E>::size() const
	{
		return count();
	}

	template<typename E>
	constexpr Flags<E>::operator bool () const
	{
		return m_value != 0;
	}

	template<typename E>
	template<typename T, typename = std::enable_if_t<std::is_integral<T>::value && sizeof(T) >= sizeof(bitfield)>>
	constexpr Flags<E>::operator T () const
	{
		return m_value;
	}

	template<typename E>
	constexpr Flags<E> Flags<E>::operator ~ () const
	{
		return Flags((~m_value) & value_mask);
	}

	template<typename E>
	constexpr Flags<E> Flags<E>::operator & (const Flags& rhs) const
	{
		return Flags(m_value & rhs.m_value);
	}

	template<typename E>
	constexpr Flags<E> Flags<E>::operator | (const Flags& rhs) const
	{
		return Flags(m_value | rhs.m_value);
	}

	template<typename E>
	constexpr Flags<E> Flags<E>::operator ^ (const Flags& rhs) const
	{
		return Flags((m_value ^ rhs.m_value) & value_mask);
	}

	template<typename E>
	constexpr bool Flags<E>::operator == (const Flags& rhs) const
	{
		return m_value == rhs.m_value;
	}

	template<typename E>
	constexpr bool Flags<E>::operator != (const Flags& rhs) const
	{
		return !operator == rhs;
	}

	template<typename E>
	constexpr Flags<E>& Flags<E>::operator |= (const Flags& rhs)
	{
		m_value |= rhs.m_value;

		return *this;
	}

	template<typename E>
	constexpr Flags<E>& Flags<E>::operator &= (const Flags& rhs)
	{
		m_value &= rhs.m_value;

		return *this;
	}

	template<typename E>
	constexpr Flags<E>& Flags<E>::operator ^= (const Flags& rhs)
	{
		m_value ^= rhs.m_value;
		m_value &= value_mask;

		return *this;
	}

	template<typename E>
	constexpr auto Flags<E>::get_flag_value(E enum_val) -> bitfield
	{
		if constexpr(auto_flag)
			return 1u << static_cast<bitfield>(enum_val);

		else
			return static_cast<bitfield>(enum_val);
	}

	template<typename T>
	constexpr Flags<T>::iterator::iterator(bitfield remaining_flags) : m_remaining_flags(remaining_flags)
	{}

	template<typename T>
	auto Flags<T>::iterator::operator ++ (int) -> iterator
	{
		iterator copy(*this);
		operator ++ ();

		return copy;
	}

	template<typename T>
	auto Flags<T>::iterator::operator ++ () -> iterator&
	{
		uint idx = find_first_bit(m_remaining_flags);
		assert(idx != 0);
		m_remaining_flags = clear_bit(m_remaining_flags, static_cast<bitfield>(idx - 1));

		return *this;
	}

	template<typename T>
	constexpr bool Flags<T>::iterator::operator == (const iterator& rhs) const
	{
		return m_remaining_flags == rhs.m_remaining_flags;
	}

	template<typename T>
	constexpr bool Flags<T>::iterator::operator != (const iterator& rhs) const
	{
		return !operator == rhs;
	}

	template<typename T>
	auto Flags<T>::iterator::operator * () const -> value_type
	{
		uint idx = find_first_flag(m_remaining_flags);
		assert(idx != 0);

		if constexpr(auto_flag)
			return static_cast<T>(idx - 1);

		else
			return static_cast<T>(1u << ((idx) - 1));
	}

	template<typename E>
	constexpr Flags<E> operator & (E lhs, Flags<E> rhs)
	{
		return rhs & lhs;
	}

	template<typename E>
	constexpr Flags<E> operator | (E lhs, Flags<E> rhs)
	{
		return rhs | lhs;
	}

	template<typename E>
	constexpr Flags<E> operator ^ (E lhs, Flags<E> rhs)
	{
		return rhs ^ lhs;
	}

	namespace FlagsOperators
	{
		template<typename E>
		constexpr std::enable_if_t<IsEnumFlag<E>::value, Flags<E>> operator ~ (E lhs)
		{
			return ~Flags<E>(lhs);
		}
		
		template<typename E>
		constexpr std::enable_if_t<IsEnumFlag<E>::value, Flags<E>> operator & (E lhs, E rhs)
		{
			return Flags<E>(lhs) & rhs;
		}
		
		template<typename E>
		constexpr std::enable_if_t<IsEnumFlag<E>::value, Flags<E>> operator | (E lhs, E rhs)
		{
			return Flags<E>(lhs) | rhs;
		}

		template<typename E>
		constexpr std::enable_if_t<IsEnumFlag<E>::value, Flags<E>> operator ^ (E lhs, E rhs)
		{
			return Flags<E>(lhs) ^ rhs;
		}
	} // namespace FlagsOperators
	
} // namespace pf

namespace std
{
	template<typename E>
	struct hash<pf::Flags<E>>
	{
		size_t operator () (const pf::Flags<E>& flags)
		{
			using underlying_type = typename pf::Flags<E>::bitfield;
			using hasher = hash<underlying_type>;
			hasher _hasher;
			
			return _hasher(static_cast<underlying_type>(flags));
		}
	};
} // namespace std

#endif // _PF_UTILS_FLAGS_inl_