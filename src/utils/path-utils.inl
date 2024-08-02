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

#ifndef _PF_UTILS_PATH_UTILS_inl_
#define _PF_UTILS_PATH_UTILS_inl_

#include "include/utils/path-utils.hpp"

namespace pf
{
    [[nodiscard]] inline std::string path_2_string(const std::filesystem::path& path)
	{
    #if PF_CHECK_CPP_VER(PF_CPP20) && (!defined(PF_PLATFORM_ANDROID) || PF_CHECK_NDK_VER(26))

		return from_utf8_string(path.generic_u8string());

    #else // (NOT) PF_CHECK_CPP_VER(PF_CPP20) && (!defined(PF_PLATFORM_ANDROID) || PF_CHECK_NDK_VER(26))

		return path.generic_u8string();

    #endif // PF_CHECK_CPP_VER(PF_CPP20) && (!defined(PF_PLATFORM_ANDROID) || PF_CHECK_NDK_VER(26))
	}
	[[nodiscard]] inline std::filesystem::path utf8_Path(std::string_view path)
	{
    #if PF_CHECK_CPP_VER(PF_CPP20) && (!defined(PF_PLATFORM_ANDROID) || PF_CHECK_NDK_VER(26))

		return std::filesystem::path(to_utf8_string(path));
    
    #else // (NOT) PF_CHECK_CPP_VER(PF_CPP20) && (!defined(PF_PLATFORM_ANDROID) || PF_CHECK_NDK_VER(26))
	
    	return std::filesystem::u8path(path);
    
    #endif // PF_CHECK_CPP_VER(PF_CPP20) && (!defined(PF_PLATFORM_ANDROID) || PF_CHECK_NDK_VER(26))
	}
} // namespace pf

#endif // _PF_UTILS_PATH_UTILS_inl_