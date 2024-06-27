#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_RAYCAST_HPP
#define PixelForge_RAYCAST_HPP

// std
#include <random>
#include <array>
#include <cstdint>

#include "BVH.hpp"
#include "vector.hpp"
#include "ray.hpp"

namespace pf
{
    class Raycast
    {
    public:
        Raycast(BVH& bvh, uint16_t ray_intersection_count = 1, uint16_t multisampling_count = 1);

        void cast_rays(std::array<Ray3, m_ray_intersection_count>& rays);

        const std::array<bool, m_ray_intersection_count> results = m_results;
    
    private:
        BVH& m_bvh;
        uint16_t m_ray_intersection_count;
        uint16_t m_multisampling_count;
        std::array<bool, m_ray_intersection_count> m_results;
        std::mt19937 m_rng;
        std::uniform_real_distribution<float> m_distribution;

        bool intersect(const Ray3& ray) const;
        std::array<Ray3, m_ray_intersection_count> generate_sampled_rays(const Ray3& ray) const;
    };
} // namespace pf


#endif // PixelForge_RAYCAST_HPP