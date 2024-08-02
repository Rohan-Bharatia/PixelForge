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

#ifndef _PF_UTILS_FUNCTION_REF_hpp_
#define _PF_UTILS_FUNCTION_REF_hpp_

// std
#include <type_traits>

#include "prerequisites.h"

namespace pf
{
    template<typename T>
	class FunctionRef;

	template<typename Ret, typename... Args>
	class FunctionRef<Ret(Args...)>
	{
	public:
		using Functor = Ret(*)(Args...);

		FunctionRef(std::nullptr_t) noexcept;
		template<typename F, typename = std::enable_if_t<std::is_invocable_r_v<Ret, F&&, Args...> && !std::is_same_v<std::decay_t<F>, FunctionRef>>> FunctionRef(F&& f) noexcept;
		FunctionRef(const FunctionRef&) noexcept = default;
		FunctionRef(FunctionRef&&) noexcept = default;
		~FunctionRef() = default;

		template<typename... CallArgs, typename = std::enable_if_t<std::is_invocable_r_v<Ret, Functor, CallArgs...>>>
        Ret operator () (CallArgs&&... args) const;

		explicit operator bool() const;

		FunctionRef& operator = (const FunctionRef&) noexcept = default;
		FunctionRef& operator = (FunctionRef&&) noexcept = default;

	private:
		using Callback = Ret(*)(void* functor, Args...);

		Callback m_callback;
		void* m_functor;
	};

	template<typename Ret, typename... Args>
	FunctionRef(Ret(*)(Args...)) -> FunctionRef<Ret(Args...)>;
} // namespace pf

#include "src/utils/function-ref.inl"

#endif // _PF_UTILS_FUNCTION_REF_hpp_