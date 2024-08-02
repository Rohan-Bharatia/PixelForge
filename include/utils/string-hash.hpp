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

#ifndef _PF_UTILS_STRING_HASH_hpp_
#define _PF_UTILS_STRING_HASH_hpp_

// std
#include <string>
#include <string_view>

#include "prerequisites.h"

namespace pf
{
    template<typename T = char>
	struct StringHash
	{
		using hash_type = std::hash<std::basic_string_view<T>>;
		using is_transparent = void;

		size_t operator () (const T* str) const;
		size_t operator () (std::basic_string_view<T> str) const;
		template<typename Allocator>
        size_t operator () (const std::basic_string<T, std::char_traits<T>, Allocator>& str) const;
	};
} // namespace pf

#include "src/utils/string-hash.inl"

#endif // _PF_UTILS_STRING_HASH_hpp_