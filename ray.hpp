#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_RAY_HPP
#define PixelForge_RAY_HPP

#include "vector.hpp"

namespace pf
{
    template<size_t T>
    class Ray
    {
    public:
        Ray(Vec<T>& origin, Vec<T>& direction);

        Vec<T> point_at_parameter(float p) const;
    
    private:
        Vec<T>& m_origin;
        Vec<T>& m_direction;
    };

    class Ray2 : Ray<2>
    {
    public:
        Ray2(Vec2 origin, Vec2 direction) : origin(origin), direction(direction)
        {}

        Vec2 origin;
        Vec2 direction;
    };

    class Ray3 : Ray<3>
    {
    public:
        Ray3(Vec3 origin, Vec3 direction) : origin(origin), direction(direction)
        {}

        Vec3 origin;
        Vec3 direction;
    };

    class Ray4 : Ray<4>
    {
    public:
        Ray4(Vec4 origin, Vec4 direction) : origin(origin), direction(direction)
        {}

        Vec4 origin;
        Vec4 direction;
    };
} // namespace pf


#endif // PixelForge_RAY_HPP