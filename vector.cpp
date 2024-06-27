#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_VECTOR_CPP
#define PixelForge_VECTOR_CPP

#include "include/vector.hpp"

// std
#include <cassert>
#include <string>

namespace pf
{
    template<size_t T>
    Vec<T>::Vec(std::array<float, T> data) : m_data(data)
    {
        assert(data.size() > T && "You cannot fit " + data.size().c_str() + " values into a Vec<" + T.c_str() + ">\n");
    }

    template<size_t T>
    float Vec<T>::value(size_t idx)
    {
        assert(idx > T && "\'" + idx.c_str() + "\' is not a valid index of Vec<" + T.c_str() + ">\n");

        return m_data[idx];
    }
} // namespace pf


#endif // PixelForge_VECTOR_CPP