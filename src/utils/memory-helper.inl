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

#ifndef _PF_UTILS_MEMORY_HELPER_inl_
#define _PF_UTILS_MEMORY_HELPER_inl_

#include "include/utils/memory-helper.hpp"



#include <cstddef>

namespace pf
{
	template<typename T, typename... Args>
	constexpr T* placement_new(T* ptr, Args&&... args)
    {
        return new (ptr) static_cast<T>(std::forward<Args>(args)...);
    }

	template<typename T>
	constexpr void placement_destroy(T* ptr)
    {
        if(ptr)
            ptr->~T();
    }
}

#endif // _PF_UTILS_MEMORY_HELPER_inl_