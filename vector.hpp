#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_VECTOR_HPP
#define PixelForge_VECTOR_HPP

// std
#include <stddef.h>
#include <array>

namespace pf
{
    template<size_t T>
    class Vec
    {
    public:
        Vec(std::array<float, T> data);

        float value(size_t idx);
    
    private:
        std::array<float, T> m_data;
    };

    class Vec2 : Vec<2>
    {
    public:
        Vec2(float x, float y) : x(x), y(y)
        {}

        float x;
        float y;
    };
    class Vec3 : Vec<3>
    {
    public:
        Vec3(float x, float y, float z) : x(x), y(y), z(z)
        {}

        float x;
        float y;
        float z;
    };
    class Vec4 : Vec<4>
    {
    public:
        Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
        {}

        float x;
        float y;
        float z;
        float w;
    };
} // namespace pf


#endif // PixelForge_VECTOR_HPP