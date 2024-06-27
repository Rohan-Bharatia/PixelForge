#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_BBOX_CPP
#define PixelForge_BBOX_CPP

#include "include/bbox.hpp"

// std
#include <limits>

namespace pf
{

    BBox::BBox() : m_min(Vec3(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max())),
                   m_max(Vec3(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()))
    {}

    BBox::BBox(Vec3& min, Vec3& max) : m_min(min), m_max(max)
    {}

    BBox BBox::combine(BBox a, BBox b)
    {
        Vec3 min(std::min(a.min.x, b.min.x),
                 std::min(a.min.y, b.min.y),
                 std::min(a.min.z, b.min.z));
        Vec3 max(std::min(a.max.x, b.max.x),
                 std::min(a.max.y, b.max.y),
                 std::min(a.max.z, b.max.z));

        return BBox(min, max);
    }

    bool BBox::intersect(const Ray3& ray, float& tmin, float& tmax) const
    {
        float t1;
        float t2;

        tmin = (min.x - ray.origin.x) / ray.direction.x;
        tmax = (min.x - ray.origin.x) / ray.direction.x;

        if (tmin > tmax)
            std::swap(tmin, tmax);

        t1 = (min.x - ray.origin.x) / ray.direction.x;
        t2 = (min.x - ray.origin.x) / ray.direction.x;

        if (t1 > t2)
            std::swap(t1, t2);

        tmin = std::max(tmin, t1);
        tmax = std::min(tmax, t2);

        if (tmin > tmax)
            return false;

        t1 = (min.y - ray.origin.y) / ray.direction.y;
        t2 = (min.y - ray.origin.y) / ray.direction.y;

        if (t1 > t2)
            std::swap(t1, t2);

        tmin = std::max(tmin, t1);
        tmax = std::min(tmax, t2);

        if (tmin > tmax)
            return false;
        
        t1 = (min.z - ray.origin.z) / ray.direction.z;
        t2 = (min.z - ray.origin.z) / ray.direction.z;

        if (t1 > t2)
            std::swap(t1, t2);

        tmin = std::max(tmin, t1);
        tmax = std::min(tmax, t2);

        if (tmin > tmax)
            return false;

        return true;

        return true;
    }

    Vec3 BBox::center() const
    {
        return Vec3((min.x + max.x) / 2,
                    (min.y + max.y) / 2,
                    (min.z + max.z) / 2);
    }
} // namespace pf


#endif // PixelForge_BBOX_CPP