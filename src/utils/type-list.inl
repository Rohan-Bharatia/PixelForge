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

#ifndef _PF_UTILS_TYPE_LIST_inl_
#define _PF_UTILS_TYPE_LIST_inl_

#include "include/utils/type-list.hpp"

namespace pf
{
    namespace Detail
	{
		template<typename NewType, typename... ListTypes>
		struct ListAppend<TypeList<ListTypes...>, NewType>
        {
            using result = TypeList<ListTypes..., NewType>;
        };

		template<template<typename> typename Functor, typename T, typename... ListTypes>
		struct ListApply<TypeList<T, ListTypes...>, Functor>
		{
			template<typename... Args>
			static void apply(Args&&... args)
			{
				Functor<T>()(std::forward<Args>(args)...);
				if constexpr(sizeof...(ListTypes) > 0)
					ListApply<TypeList<ListTypes...>, Functor>::apply(std::forward<Args>(args)...);
			}
		};

		template<typename T, typename... ListTypes>
		struct ListAt<TypeList<T, ListTypes...>, 0>
		{
			using type = T;
		};

        template<size_t Index, typename T, typename... ListTypes>
		struct ListAt<TypeList<T, ListTypes...>, Index>
		{
			static_assert(Index <= sizeof...(ListTypes), "Index out of range!");

			using type = typename ListAt<TypeList<ListTypes...>, Index - 1>::type;
		};

		template<typename... First, typename... Second>
		struct ListConcat<TypeList<First...>, TypeList<Second...>>
		{
			using result = TypeList<First..., Second...>;
		};

        struct ListFindHelper
		{
			template<size_t Index, typename ToFind, typename Type, typename... Rest> static constexpr size_t find()
			{
				if constexpr(std::is_same_v<ToFind, Type>)
					return Index;
				else
					return find<Index + 1, ToFind, Rest...>();
			}

			template<size_t Index, typename ToFind> static constexpr size_t find()
			{
				return std::numeric_limits<size_t>::max();
			}
		};

		template<typename TypeToFind, typename... ListTypes>
		struct ListFind<TypeList<ListTypes...>, TypeToFind>
		{
			static constexpr size_t find()
			{
				return ListFindHelper::find<0, TypeToFind, ListTypes...>();
			}
		};

		template<template<typename...> typename Class, typename... ListTypes>
		struct ListInstantiate<TypeList<ListTypes...>, Class>
		{
			using result = Class<ListTypes...>;
		};


		template<typename NewType, typename... ListTypes>
		struct ListPrepend<TypeList<ListTypes...>, NewType>
		{
			using result = TypeList<NewType, ListTypes...>;
		};


		template<typename... ListTypes>
		struct ListSize<TypeList<ListTypes...>>
		{
			static constexpr size_t size = sizeof...(ListTypes);
		};

		template<typename L1, typename L2, template<typename> typename Transformer>
		struct ListTransformHelper;

		template<typename... Transformed, typename T, typename... Rest, template<typename> typename Transformer>
		struct ListTransformHelper<TypeList<Transformed...>, TypeList<T, Rest...>, Transformer>
		{
			using result = typename ListTransformHelper<TypeList<Transformed..., typename Transformer<T>::type>, TypeList<Rest...>, Transformer>::Result;
		};

		template<typename... Transformed, template<typename> typename Transformer>
		struct ListTransformHelper<TypeList<Transformed...>, TypeList<>, Transformer>
		{
			using result = TypeList<Transformed...>;
		};

		template<typename... ListTypes, template<typename> typename Transformer>
		struct ListTransform<TypeList<ListTypes...>, Transformer>
		{
			using result = typename ListTransformHelper<TypeList<>, TypeList<ListTypes...>, Transformer>::Result;
		};


		template<typename... Types, typename T1>
		struct ListUnique<TypeList<Types...>, TypeList<T1>>
		{
			static constexpr bool is_type_present = type_list_has<TypeList<Types...>, T1>;
			using Result = std::conditional_t<!is_type_present, TypeList<Types..., T1>, TypeList<Types...>>;
		};

		template<>
		struct ListUnique<TypeList<>, TypeList<>>
		{
			using result = TypeList<>;
		};

		template<typename... Types, typename T1, typename T2, typename... Rest>
		struct ListUnique<TypeList<Types...>, TypeList<T1, T2, Rest...>>
		{
			using result = typename ListUnique<typename ListUnique<TypeList<Types...>, TypeList<T1>>::Result, TypeList<T2, Rest...>>::Result;
		};
	} // namespace Detail
    
    template<typename List, template<typename> typename Functor, typename... Args>
	void type_list_apply(Args&&... args)
    {
        if constexpr(!type_list_empty<List>)
			Detail::ListApply<List, Functor>::apply(std::forward<Args>(args)...);
    }
} // namespace pf

#endif // _PF_UTILS_TYPE_LIST_inl_