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

#ifndef _PF_UTILS_CALL_ON_EXIT_inl_
#define _PF_UTILS_CALL_ON_EXIT_inl_

#include "include/utils/call-on-exit.hpp"

namespace pf
{
    template<typename F>
    CallOnExit<F>::CallOnExit(F&& functor) : m_functor(std::move(functor))
    {}

    template<typename F>
    CallOnExit<F>::~CallOnExit()
    {
        if(m_functor)
            (*m_functor)();
    }

    template<typename F>
    void CallOnExit<F>::call_and_reset()
    {
        if(m_functor)
            (*m_functor)();

        reset();
    }

	template<typename F>
    void CallOnExit<F>::reset()
    {
        m_functor.reset();
    }


} // namespace pf


#endif // _PF_UTILS_CALL_ON_EXIT_inl_