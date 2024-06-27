#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_RAYCAST_CPP
#define PixelForge_RAYCAST_CPP

#include "include/raycast.hpp"

namespace pf
{
    Raycast::Raycast(BVH& bvh, uint16_t ray_intersection_count = 1, uint16_t multisampling_count = 1) : m_bvh(bvh), m_ray_intersection_count(ray_intersection_count),
                                                                                                        m_multisampling_count(multisampling_count)
    {}

    void Raycast::cast_rays(std::array<Ray3, m_ray_intersection_count>& rays)
    {
        m_results.clear();

        for(const Ray3& ray : rays)
        {
            bool hit = false;
            std::array<Ray3, m_ray_intersection_count> sampled_rays = generate_sample_rays(ray);

            for(const Ray3& sampled_ray : sampled_rays)
            {
                if(intersect(sampled_ray))
                {
                    hit = true;

                    break;
                }
            }

            m_results.push_back(hit);
        }
    }

    bool Raycast::intersect(const Ray3& ray) const
    {
        float tmin, tmax;

        for(const Node& node : m_bhv.nodes)
        {
            if(node.bounds.intersect(ray, tmin, tmax))
            {
                Vec3& primitive = m_bvh.Primitives[node.obj_idx];

                for(size_t i = 0; i < 3; i++)
                {
                    if(m_bvh.intersect_triangle(primitive, ray, tmin))
                        return true;
                }
            }
        }

        return false;
    }

    std::array<Ray3, m_ray_intersection_count> Raycast::generate_sampled_rays(const Ray3& ray) const
    {
        std::array<Ray3, m_multisampling_count> sampled_rays;

        for(int i = 0; i < sampled_rays.size(); i++)
        {
            Vec3 jitter(m_distribution(m_rng), m_distribution(m_rng), m_distribution(m_rng));
            Vec3 sampled_ray(ray.origin, ray.direction + jitter);
            sampled_rays[i] = sampled_ray;
        }

        return sampled_rays;
    }
} // namespace pf


#endif // PixelForge_RAYCAST_CPP