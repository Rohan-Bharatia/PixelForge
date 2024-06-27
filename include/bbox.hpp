#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_BBOX_HPP
#define PixelForge_BBOX_HPP

// std
#include <array>
#include <algorithm>

#include "ray.hpp"

namespace pf
{
    class BBox
    {
    public:
        BBox();
        BBox(Vec3& min, Vec3& max);

        static BBox combine(BBox a, BBox b);
        bool intersect(const Ray3& ray, float& tmin, float& tmax) const;

        Vec3 center() const;

        const Vec3 min = m_min;
        const Vec3 max = m_max;
    
    private:
        Vec3 m_min;
        Vec3 m_max;
    };
} // namespace pf


#endif // PixelForge_BBOX_HPP