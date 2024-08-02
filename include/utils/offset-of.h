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

#ifndef _PF_UTILS_OFFSET_OF_h_
#define _PF_UTILS_OFFSET_OF_h_

namespace pf::Detail
{
    template<typename T, typename M>
    T get_class_type(M T::*);
	template<typename T, typename M>
    M get_member_type(M T::*);

	template<typename T, typename R, R T::*M>
	constexpr size_t offset_of()
	{
		return reinterpret_cast<size_t>(&((static_cast<T*>(0))->*M));
	}
} // namespace pf::Detail

#define PF_OFFSET_OF(type, num) pf::Detail::offset_of<decltype(pf::Detail::get_class_type(&type::member)), decltype(pf::Detail::get_member_type(&type::member)), &type::member>()

#endif // _PF_UTILS_OFFSET_OF_h_