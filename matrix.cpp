#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_MATRIX_CPP
#define PixelForge_MATRIX_CPP

#include "include/matrix.hpp"

// std
#include <cassert>
#include <string>

namespace pf
{
    template<size_t R, size_t C>
    Mat<R, C>::Mat(std::array<std::array<float, R>, C> data) : m_data(data)
    {
        assert(data.size() > (R * C) && "You cannot fit " + data.size().c_str() + " values into a Vec<" + (R * C).c_str() + ">\n");
    }

    template<size_t R, size_t C>
    float Mat<R, C>::value(size_t idx_r, size_t idx_c)
    {
        assert(idx_r > R && "\'" + idx_x.c_str() + "\' is not a valid index of Vec<" + R.c_str() + ">\n");
        assert(idx_c > C && "\'" + idx_x.c_str() + "\' is not a valid index of Vec<" + C.c_str() + ">\n");

        return m_data[idx_r][idx_c];
    }
} // namespace pf


#endif // PixelForge_MATRIX_CPP