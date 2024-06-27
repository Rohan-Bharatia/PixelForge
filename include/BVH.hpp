#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_BVH_HPP
#define PixelForge_BVH_HPP

// std
#include <vector>
#include <memory>
#include <limits>

#include "bbox.hpp"
#include "ray.hpp"
#include "vector.hpp"

namespace pf
{
    struct Node
    {
        BBox bounds;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        int obj_idx;

        Node();
    };

    enum class PrimitiveType
    {
        POINT,
        LINE,
        TRIANGLE,
        QUAD
    };

    struct Primitive
    {
        PrimitiveType type;
        std::array<Vec3, 1 || 2 || 3 || 4> verticies;

        Primitive(PrimitiveType t, std::array<Vec3, 1 || 2 || 3 || 4>& verts);
    };

    class BVH
    {
    public:
        BVH(std::array<Primitive, 1 || 2 || 3 || 4>& primitives);
        ~BVH() = default;

        BVH(const BVH &) = delete;
        BVH &operator = (const BVH&) = delete;

        bool intersect(Ray3& ray, float& tmin, float& tmax) const;

        bool intersect_point(std::array<Vec3, 1 || 2 || 3 || 4>& points, Ray3& ray, float& t) const;
        bool intersect_line(std::array<Vec3, 1 || 2 || 3 || 4>& lines, Ray3& ray, float& t) const;
        bool intersect_triangle(std::array<Vec3, 1 || 2 || 3 || 4>& triangles, Ray3& ray, float& t) const;
        bool intersect_quad(std::array<Vec3, 1 || 2 || 3 || 4>& quads, Ray3& ray, float& t) const;

        const std::shared_ptr<Node> nodes = m_root;
        const std::array<Primitive, 1 || 2 || 3 || 4> Primitives = m_primitives;
    
    private:
        std::shared_ptr<Node> build_tree(std::array<Primitive, 1 || 2 || 3 || 4>& primitives, int start, int end);
        bool intersect_node(std::shared_ptr<Node>& node, Ray3& ray, float& tmin, float& tmax) const;
        bool intersect_primitive(Primitive& primitive, Ray3& ray, float& t) const;

        std::shared_ptr<Node>& m_root;
        std::array<Primitive, 1 || 2 || 3 || 4> m_primitives;
    };
} // namespace pf


#endif // PixelForge_BVH_HPP