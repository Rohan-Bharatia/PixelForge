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

#ifndef _PF_UTILS_CALL_ON_EXIT_hpp_
#define _PF_UTILS_CALL_ON_EXIT_hpp_

// std
#include <optional>

#include "prerequisites.h"

#define PF_DEFER(expr) pf::CallOnExit pf_suffix_macro(defer_, __LINE__)([&] { expr })

namespace pf
{
    template<typename F>
    class CallOnExit
    {
    public:
        CallOnExit() = default;
		CallOnExit(F&& functor);
		CallOnExit(const CallOnExit&) = delete;
		CallOnExit(CallOnExit&&) = delete;
		~CallOnExit();

		void call_and_reset();
		void reset();

		CallOnExit& operator = (const CallOnExit&) = delete;
		CallOnExit& operator = (CallOnExit&&) = default;

	private:
		std::optional<F> m_functor;
    };
} // namespace pf

#include "src/utils/call-on-exit.inl"

#endif // _PF_UTILS_CALL_ON_EXIT_hpp_