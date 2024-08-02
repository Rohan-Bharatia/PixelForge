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

#ifndef _PF_UTILS_FUNCTION_TRAITS_h_
#define _PF_UTILS_FUNCTION_TRAITS_h_

// std
#include <type_traits>

#include "prerequisites.h"
#include "concepts.h"
#include "type-list.hpp"

namespace pf
{
    template<typename T>
	struct FunctionTraits : FunctionTraits<decltype(&T::operator())>
	{};

	template<typename Ret, typename... Args>
	struct FunctionTraits<Ret(Args...)>
	{
		using FuncType   = Ret(Args...);
		using ReturnType = Ret;

		using ArgTypes                   = TypeList<Args...>;
		static constexpr size_t ArgCount = sizeof...(Args);

		template<size_t I>
		struct Arg
		{
			static_assert(I < ArgCount, "argument out of range!");
			using type = TypeListAt<ArgTypes, I>;
		};

		template<size_t I>
		using ArgType = typename Arg<I>::type;
	};

	template<typename Ret, typename... Args>
	struct FunctionTraits<Ret(*)(Args...)> : FunctionTraits<Ret(Args...)>
    {};

	template<typename T, typename Ret, typename... Args>
	struct FunctionTraits<Ret(T::*)(Args...)> : FunctionTraits<Ret(Args...)>
    {};

	template<typename T, typename Ret, typename... Args>
	struct FunctionTraits<Ret(T::*)(Args...) &> : FunctionTraits<Ret(Args...)>
    {};

	template<typename T, typename Ret, typename... Args>
	struct FunctionTraits<Ret(T::*)(Args...) &&> : FunctionTraits<Ret(Args...)>
    {};

	template<typename T, typename Ret, typename... Args>
	struct FunctionTraits<Ret(T::*)(Args...) const> : FunctionTraits<Ret(Args...)>
    {};

	template<typename T, typename Ret, typename... Args>
	struct FunctionTraits<Ret(T::*)(Args...) const&> : FunctionTraits<Ret(Args...)>
    {};

	template<typename T, typename Ret, typename... Args>
	struct FunctionTraits<Ret(T::*)(Args...) const&&> : FunctionTraits<Ret(Args...)>
    {};

	template<typename T, typename Ret, typename... Args>
	struct FunctionTraits<Ret(T::*)(Args...) volatile> : FunctionTraits<Ret(Args...)>
    {};

	template<typename T, typename Ret, typename... Args>
	struct FunctionTraits<Ret(T::*)(Args...) volatile&> : FunctionTraits<Ret(Args...)>
    {};

	template<typename T, typename Ret, typename... Args>
	struct FunctionTraits<Ret(T::*)(Args...) volatile&&> : FunctionTraits<Ret(Args...)>
    {};

	template<typename T, typename Ret, typename... Args>
	struct FunctionTraits<Ret(T::*)(Args...) const volatile> : FunctionTraits<Ret(Args...)>
    {};

	template<typename T, typename Ret, typename... Args>
	struct FunctionTraits<Ret(T::*)(Args...) const volatile&> : FunctionTraits<Ret(Args...)>
    {};

	template<typename T, typename Ret, typename... Args>
	struct FunctionTraits<Ret(T::*)(Args...) const volatile&&> : FunctionTraits<Ret(Args...)>
    {};

	template<typename T>
	struct FunctionTraits<const T> : FunctionTraits<T>
    {};

	template<typename T>
	struct FunctionTraits<const T&> : FunctionTraits<T>
    {};

	template<typename T>
	struct FunctionTraits<const T&&> : FunctionTraits<T>
    {};

	template<typename T>
	struct FunctionTraits<T&> : FunctionTraits<T>
    {};

	template<typename T>
	struct FunctionTraits<T&&> : FunctionTraits<T>
    {};

	template<typename, typename = void>
	struct IsFunctor : std::false_type
    {};

	template<typename T>
	struct IsFunctor<T, std::enable_if_t<std::is_function_v<T>>> : std::true_type
    {};

	template<typename T>
	struct IsFunctor<T, std::enable_if_t<std::is_member_function_pointer_v<T>>> : std::true_type
    {};

	template<typename T>
	struct IsFunctor<T, std::void_t<decltype(&T::operator())>> : std::true_type
    {};

	template<typename T>
	constexpr bool is_functor = IsFunctor<T>::value;

	PF_CONCEPT(template<typename T> concept Functor = is_functor<T>;)

	template<typename... Args>
	struct OverloadResolver
	{
		template<typename R, typename T>
		constexpr auto operator () (R(T::* ptr)(Args...)) const noexcept
		{
			return ptr;
		}

		template<typename R, typename T>
		constexpr auto operator () (R(T::* ptr)(Args...)&) const noexcept
		{
			return ptr;
		}

		template<typename R, typename T>
		constexpr auto operator () (R(T::* ptr)(Args...)&&) const noexcept
		{
			return ptr;
		}

		template<typename R, typename T>
		constexpr auto operator () (R(T::* ptr)(Args...) const) const noexcept
		{
			return ptr;
		}

		template<typename R, typename T>
		constexpr auto operator () (R(T::* ptr)(Args...) const&) const noexcept
		{
			return ptr;
		}

		template<typename R, typename T>
		constexpr auto operator () (R(T::* ptr)(Args...) const&&) const noexcept
		{
			return ptr;
		}

		template<typename R>
		constexpr auto operator () (R(*ptr)(Args...)) const noexcept
		{
			return ptr;
		}
	};

	template<typename... Args>
    constexpr OverloadResolver<Args...> Overload = {};
} // namespace pf

#endif // _PF_UTILS_FUNCTION_TRAITS_h_