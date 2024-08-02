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

#ifndef _PF_UTILS_PATH_UTILS_hpp_
#define _PF_UTILS_PATH_UTILS_hpp_

// std
#include <filesystem>
#include <string>

#include "prerequisites.h"
#include "string-utils.hpp"

namespace pf
{
    [[nodiscard]] inline std::string path_2_string(const std::filesystem::path& path);
	[[nodiscard]] inline std::filesystem::path utf8_path(std::string_view path);
} // namespace pf

#include "src/utils/path-utils.inl"

#endif // _PF_UTILS_PATH_UTILS_hpp_