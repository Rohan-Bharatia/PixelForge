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

#ifndef _PF_UTILS_MOVABLE_PTR_hpp_
#define _PF_UTILS_MOVABLE_PTR_hpp_

namespace pf
{
    template<typename T>
    class MovablePtr
    {
    public:
        MovablePtr(T* value = nullptr);
		MovablePtr(const MovablePtr&) = default;
		MovablePtr(MovablePtr&& ptr) noexcept;
		~MovablePtr() = default;

        T* get();

        T* operator -> () const;

		operator T* () const;

		MovablePtr& operator = (T* value);
		MovablePtr& operator = (const MovablePtr&) = default;
		MovablePtr& operator = (MovablePtr&& ptr) noexcept;
    
    private:
        T* m_value;
    };
} // namespace pf

#include "src/utils/movable-ptr.inl"

#endif // _PF_UTILS_MOVABLE_PTR_hpp_