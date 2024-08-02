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

#ifndef _PF_UTILS_MOVABLE_PTR_inl_
#define _PF_UTILS_MOVABLE_PTR_inl_

#include "include/utils/movable-ptr.hpp"

namespace pf
{
    template<typename T>
    MovablePtr<T>::MovablePtr(T* value = nullptr) : m_value(value)
    {}

	template<typename T>
    MovablePtr<T>::MovablePtr(MovablePtr&& ptr) noexcept : m_value(ptr.m_value)
    {
        ptr.m_value = nullptr;
    }

    template<typename T>
    T* MovablePtr<T>::get()
    {
        return m_value;
    }

    template<typename T>
    T* MovablePtr<T>::operator -> () const
    {
        return m_value;
    }

	template<typename T>
    MovablePtr<T>::operator T* () const
    {
        return m_value;
    }

	template<typename T>
    MovablePtr<T>& MovablePtr<T>::operator = (T* value)
    {
        m_value = value;

        return *this;
    }

	template<typename T>
    MovablePtr<T>& MovablePtr<T>::operator = (MovablePtr&& ptr) noexcept
    {
        std::swap(m_value, ptr.m_value);

        return *this;
    }
} // namespace pf

#endif // _PF_UTILS_MOVABLE_PTR_inl_