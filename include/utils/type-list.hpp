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

#ifndef _PF_UTILS_TYPE_LIST_hpp_
#define _PF_UTILS_TYPE_LIST_hpp_

// std
#include <cstddef>
#include <limits>

#include "prerequisites.h"

namespace pf
{
    template<typename...>
    struct TypeList
    {};

    namespace Detail
	{
		template<typename, typename>
		struct ListAppend;

		template<typename, template<typename> typename>
		struct ListApply;

		template<typename, size_t>
		struct ListAt;

		template<typename, typename>
		struct ListConcat;

		template<typename, typename>
		struct ListFind;

		template<typename, template<typename...> typename>
		struct ListInstantiate;

		template<typename, typename>
		struct ListPrepend;

		template<typename>
		struct ListSize;

		template<typename, template<typename...> typename>
		struct ListTransform;

		template<typename, typename>
		struct ListUnique;
	} // namespace Detail

    template<typename List, typename NewType>
	using type_list_append = typename Detail::ListAppend<List, NewType>::result;

	template<typename List, template<typename> typename Functor, typename... Args>
	void type_list_apply(Args&&... args);

	template<typename List, size_t Index>
	using type_aist_at = typename Detail::ListAt<List, Index>::type;

	template<typename FirstList, typename SecondList>
	using type_list_concat = typename Detail::ListConcat<FirstList, SecondList>::result;

	template<typename List>
	constexpr bool type_list_empty = Detail::ListSize<List>::Size == 0;

	template<typename List, typename Type>
	constexpr size_t type_list_find = Detail::ListFind<List, Type>::Find();

	template<typename List, typename Type>
	constexpr bool type_list_has = type_list_find<List, Type> != std::numeric_limits<size_t>::max();

	template<typename List, template<typename...> typename Class>
	using type_list_instantiate = typename Detail::ListInstantiate<List, Class>::result;

	template<typename List, typename NewType>
	using type_list_prepend = typename Detail::ListPrepend<List, NewType>::result;

	template<typename List>
	constexpr size_t type_list_size = Detail::ListSize<List>::Size;

	template<typename List, template<typename> typename Transformer>
	using type_list_transform = typename Detail::ListTransform<List, Transformer>::result;

	template<typename List>
	using type_list_unique = typename Detail::ListUnique<TypeList<>, List>::result;
} // namespace pf

#include "src/utils/type-list.inl"

#endif // _PF_UTILS_TYPE_LIST_hpp_