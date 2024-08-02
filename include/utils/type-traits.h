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

#ifndef _PF_UTILS_TYPE_TRAITS_h_
#define _PF_UTILS_TYPE_TRAITS_h_

// std
#include <cstddef>
#include <type_traits>

namespace pf
{
    template<typename T>
	struct AlwaysFalse : std::false_type
	{};

	template<auto T>
	struct AlwaysFalseValue : std::false_type
	{};

    template<typename T>
	struct LazyVoid
	{
	    using type = void;
	};

	template<typename T>
    using lazy_void = typename LazyVoid<T>::type;

    template<typename E, typename = void>
	struct EnumValueCount
	{
		static_assert(AlwaysFalse<E>(), "enum has no Count nor Max field!");
	};

	template<typename E>
	struct EnumValueCount<E, lazy_void<decltype(E::Count)>>
	{
		static_assert(std::is_enum_v<E>, "Type must be an enumeration!");

		static constexpr size_t value = static_cast<size_t>(E::Count);
	};

	template<typename E>
	struct EnumValueCount<E, lazy_void<decltype(E::Max)>>
	{
		static_assert(std::is_enum_v<E>, "Type must be an enumeration!");

		static constexpr size_t value = static_cast<size_t>(E::Max) + 1;
	};

	template<typename E>
    constexpr size_t enum_value_count = EnumValueCount<E>::value;
} // namespace pf


#endif // _PF_UTILS_TYPE_TRAITS_h_