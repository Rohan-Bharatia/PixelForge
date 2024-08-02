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

#ifndef _PF_UTILS_STRING_HASH_inl_
#define _PF_UTILS_STRING_HASH_inl_

#include "include/utils/string-hash.hpp"

namespace pf
{
    template<typename T>
	size_t StringHash<T>::operator()(const T* str) const
	{
		return hash_type{}(str);
	}

	template<typename T>
	size_t StringHash<T>::operator()(std::basic_string_view<T> str) const
	{
		return hash_type{}(str);
	}
	
	template<typename T>
	template<typename Allocator>
	size_t StringHash<T>::operator()(const std::basic_string<T, std::char_traits<T>, Allocator>& str) const
	{
		return hash_type{}(str);
	}
} // namespace pf

#endif // _PF_UTILS_STRING_HASH_inl_