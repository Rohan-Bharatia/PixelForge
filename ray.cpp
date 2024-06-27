#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_RAY_CPP
#define PixelForge_RAY_CPP

#include "include/ray.hpp"

// std
#include <stddef.h>

namespace pf
{
    template<size_t T>
    Ray<T>::Ray(Vec<T>& origin, Vec<T>& direction) : m_origin(origin), m_direction(direction)
    {}

    template<size_t T>
    Vec<T> Ray<T>::point_at_parameter(float p) const
    {
        std::array<float, T> m_vals;

        for(int i = 0; i < T; i++)
            m_vals.push_back(m_origin[i] + p * m_direction[i]);
        
        Vec<T> vals(m_vals);

        return vals;
    }
} // namespace pf


#endif // PixelForge_RAY_CPP