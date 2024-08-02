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

#ifndef _PF_UTILS_STRING_UTILS_hpp_
#define _PF_UTILS_STRING_UTILS_hpp_

// std
#include <string>
#include <string_view>

#include "prerequisites.h"

namespace pf
{
#if PF_CHECK_CPP_VER(PF_CPP20)

	inline std::string_view from_utf8_string(const char8_t* str);
	inline std::string from_utf8_string(const std::u8string& str);
	inline std::string_view from_utf8_string(std::u8string_view str);
    
    inline std::u8string_view to_utf8_string(const char* str);
	inline std::u8string to_utf8_string(const std::string& str);
	inline std::u8string_view to_utf8_string(std::string_view str);

#else // (NOT) PF_CHECK_CPP_VER(PF_CPP20)

	inline std::string from_utf8_string(const char* str);
	inline std::string from_utf8_string(std::string str);
	inline std::string_view from_utf8_string(std::string_view str);
    
    inline std::string to_utf8_string(const char* str);
	inline std::string to_utf8_string(std::string str);
	inline std::string_view to_utf8_string(std::string_view str);

#endif // PF_CHECK_CPP_VER(PF_CPP20)
} // namespace pf

#include "src/utils/string-utils.inl"

#endif // _PF_UTILS_STRING_UTILS_hpp_