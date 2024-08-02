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

#ifndef _PF_UTILS_TYPE_NAME_inl_
#define _PF_UTILS_TYPE_NAME_inl_

#include "include/utils/type-name.hpp"

namespace pf
{
    template<typename T>
    constexpr std::string_view type_name()
    {
        constexpr std::string_view pretty_func = PF_PRETTY_FUNCTION;

    #ifdef PF_COMPILER_MSVC

        constexpr std::string_view prefix = "PF::type_name<"sv;
		constexpr std::string_view suffixes = ">"sv;

    #else // (NOT) PF_COMPILER_MSVC

        constexpr std::string_view prefix = "T = "sv;
		constexpr std::string_view suffixes = ";]"sv;

    #endif // PF_COMPILER_MSVC

        constexpr size_t b = pretty_func.find(prefix);
		static_assert(b != pretty_func.npos);

		constexpr size_t e = pretty_func.substr(b).find_last_of(suffixes, b) + b;
		static_assert(e != pretty_func.npos);

		size_t p = b + prefix.size();

		std::string_view type_name = pretty_func.substr(p, e - p);

    #ifdef PF_COMPILER_MSVC

		for(std::string_view type_prefix : { "class "sv, "struct "sv, "enum "sv, "enum class "sv, "enum struct"sv })
		{
			if(type_name.substr(0, type_prefix.size()) == type_prefix)
			{
				type_name.remove_prefix(type_prefix.size());
                
				break;
			}
		}

    #endif // PF_COMPILER_MSVC

		return type_name;
    }
} // namespace pf

#endif // _PF_UTILS_TYPE_NAME_inl_