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

#ifndef _PF_UTILS_TYPE_TAG_h_
#define _PF_UTILS_TYPE_TAG_h_

namespace pf
{
    template<typename T>
    struct TypeTag
    {
        using type = T;
    };
} // namespace pf

#endif // _PF_UTILS_TYPE_TAG_h_