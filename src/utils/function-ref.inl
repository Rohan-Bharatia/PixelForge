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

#ifndef _PF_UTILS_FUNCTION_REF_inl_
#define _PF_UTILS_FUNCTION_REF_inl_

// std
#include <functional>
#include <memory>
#include <utility>

#include "include/utils/function-ref.hpp"

namespace pf
{
	template<typename Ret, typename ...Args>
	FunctionRef<Ret(Args...)>::FunctionRef(std::nullptr_t) noexcept : m_functor(nullptr)
	{}

    template<typename Ret, typename... Args>
	template<typename F, typename>
	FunctionRef<Ret(Args...)>::FunctionRef(F&& f) noexcept
	{
		m_functor = reinterpret_cast<void*>(std::addressof(f));
		m_callback = [](void* functor, Args... args) -> Ret
		{
			return std::invoke(*reinterpret_cast<decltype(std::addressof(f))>(functor), std::forward<Args>(args)...);
		};
	}

    template<typename Ret, typename... Args>
	template<typename... CallArgs, typename>
	Ret FunctionRef<Ret(Args...)>::operator()(CallArgs&&... args) const
	{
		return m_callback(m_functor, std::forward<CallArgs>(args)...);
	}

	template<typename Ret, typename ...Args>
	FunctionRef<Ret(Args...)>::operator bool() const
	{
		return m_functor != nullptr;
	}
}
} // namespace pf

#endif // _PF_UTILS_FUNCTION_REF_inl_