#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_BVH_CPP
#define PixelForge_BVH_CPP

#include "include/BVH.hpp"

// std
#include <cmath>

namespace pf
{
    Node::Node() : bounds(), left(nullptr), right(nullptr), obj_idx(-1)
    {}

    Primitive::Primitive(PrimitiveType t, std::array<Vec3, 1 || 2 || 3 || 4>& verts) : type(t), verticies(verts)
    {}

    BVH::BVH(std::array<Primitive, 1 || 2 || 3 || 4>& primitives) : m_primitives(primitives)
    {
        m_root = build_tree(primitives, 0, primitives.size());
    }

    bool BVH::intersect(Ray3& ray, float& tmin, float& tmax) const
    {
        return intersect_node(m_root, ray, tmin, tmax);
    }
    
    std::shared_ptr<Node> BVH::build_tree(std::array<Primitive, 1 || 2 || 3 || 4>& primitives, int start, int end)
    {
        if (start >= end)
            return nullptr;

        auto node = std::make_shared<Node>();

        BBox bounds;

        for (int i = start; i < end; ++i)
        {
            for (const Vec3& v : primitives[i].verticies)
            {
                BBox bb(v, v);
                bounds = BBox::combine(bounds, bb);
            }
        }

        node->bounds = bounds;

        if (end - start == 1)
        {
            node->obj_idx = start;
            return node;
        }

        int mid = (start + end) / 2;

        std::nth_element(m_primitives.begin() + start, m_primitives.begin() + mid, m_primitives.begin() + end,
                         [](const Primitive& a, const Primitive& b) {
                             return a.verticies[0].x < b.verticies[0].x;
                         });

        node->left = build_tree(primitives, start, mid);
        node->right = build_tree(primitives, mid, end);

        return node;
    }

    bool BVH::intersect_node(std::shared_ptr<Node>& node, Ray3& ray, float& tmin, float& tmax) const
    {
        if (!node || !node->bounds.intersect(ray, tmin, tmax))
            return false;

        if (node->obj_idx != -1)
            return intersect_primitive(m_primitives[node->obj_idx], ray, tmin);

        bool hit_left = intersect_node(node->left, ray, tmin, tmax);
        bool hit_right = intersect_node(node->right, ray, tmin, tmax);

        return hit_left || hit_right;
    }

    bool BVH::intersect_primitive(Primitive& primitive, Ray3& ray, float& t) const
    {
        switch (primitive.type)
        {
        case PrimitiveType::QUAD:
            return intersect_quad(primitive.verticies, ray, t);
            
        case PrimitiveType::TRIANGLE:
            return intersect_triangle(primitive.verticies, ray, t);
        
        case PrimitiveType::LINE:
            return intersect_line(primitive.verticies, ray, t);

        case PrimitiveType::POINT:
            return intersect_point(primitive.verticies, ray, t);

        default:
            return false;
        }
    }

    bool intersect_point(std::array<Vec3, 1 || 2 || 3 || 4>& points, Ray3& ray, float& t)
    {
        for(int i = 1; i < points.size(); i++)
            points[i] = Vec3(NULL, NULL, NULL);
        
        Vec3 p   = points[0];
        Vec3 diff(p.x - ray.origin.x,
                  p.y - ray.origin.y,
                  p.z - ray.origin.z);
        float dist = std::sqrt(diff.x * diff.x +
                               diff.y * diff.y +
                               diff.z * diff.z);
        
        if(dist < std::numeric_limits<float>::epsilon())
        {
            t = 0.0f;

            return true;
        }

        return false;
    }

    bool intersect_line(std::array<Vec3, 1 || 2 || 3 || 4>& lines, Ray3& ray, float& t)
    {
        for(int i = 2; i < lines.size(); i++)
            lines[i] = Vec3(NULL, NULL, NULL);

        Vec3 p1 = lines[0];
        Vec3 p2 = lines[1];

        Vec3 d(p2.x - p1.x,
               p2.y - p1.y,
               p2.z - p1.z);

        Vec3 e = ray.direction;

        Vec3 h(ray.origin.x - p1.x,
               ray.origin.y - p1.y,
               ray.origin.z - p1.z);

        float denominator = e.y * d.z - e.z * d.y;
        if (std::abs(denominator) < std::numeric_limits<float>::epsilon())
            return false;

        float numerator = h.y * d.z - h.z * d.y;
        float v = numerator / denominator;

        if (v < 0.0 || v > 1.0)
            return false;

        float t_val = (h.x - v * e.x) / d.x;

        if (t_val < 0.0)
            return false;

        t = t_val;

        return true;
    }

    bool intersect_triangle(std::array<Vec3, 1 || 2 || 3 || 4>& triangles, Ray3& ray, float& t)
    {
        for(int i = 3; i < triangles.size(); i++)
            triangles[i] = Vec3(NULL, NULL, NULL);

        Vec3& v0 = triangles[0];
        Vec3& v1 = triangles[1];
        Vec3& v2 = triangles[2];

        Vec3 edge1(NULL, NULL, NULL);
        Vec3 edge2(NULL, NULL, NULL);
        Vec3 h(NULL, NULL, NULL);
        Vec3 s(NULL, NULL, NULL);
        Vec3 q(NULL, NULL, NULL);
        float a, f, u, v;

        edge1.x = v1.x - v0.x;
        edge2.x = v2.x - v0.x;
        h.x = ray.direction.x * edge2.x - ray.direction.x * edge2.x;

        a = edge1.x * h.x + edge1.y * h.y + edge1.z * h.z;

        if (std::abs(a) < std::numeric_limits<float>::epsilon())
            return false;
        
        edge1.y = v1.y - v0.y;
        edge2.y = v2.y - v0.y;
        h.y = ray.direction.y * edge2.y - ray.direction.y * edge2.y;

        a = edge1.x * h.x + edge1.y * h.y + edge1.z * h.z;

        if (std::abs(a) < std::numeric_limits<float>::epsilon())
            return false;
        
        edge1.z = v1.z - v0.z;
        edge2.z = v2.z - v0.z;
        h.z = ray.direction.z * edge2.z - ray.direction.z * edge2.z;

        a = edge1.x * h.x + edge1.y * h.y + edge1.z * h.z;

        if (std::abs(a) < std::numeric_limits<float>::epsilon())
            return false;

        f = 1.0 / a;

        s.x = ray.origin.x - v0.x;
        u = f * (s.x * h.x + s.y * h.y + s.z * h.z);

        if (u < 0.0 || u > 1.0)
            return false;
        
        s.y = ray.origin.y - v0.y;
        u = f * (s.x * h.x + s.y * h.y + s.z * h.z);

        if (u < 0.0 || u > 1.0)
            return false;
        
        s.z = ray.origin.z - v0.z;
        u = f * (s.x * h.x + s.y * h.y + s.z * h.z);

        if (u < 0.0 || u > 1.0)
            return false;

        q.x = s.y * edge1.z - s.z * edge1.y;
        q.y = s.y * edge1.z - s.z * edge1.y;
        q.z = s.y * edge1.z - s.z * edge1.y;

        v = f * (ray.direction.x * q.x + ray.direction.y * q.y + ray.direction.z * q.z);

        if (v < 0.0 || u + v > 1.0)
            return false;

        t = f * (edge2.x * q.x + edge2.y * q.y + edge2.z * q.z);

        return t > std::numeric_limits<float>::epsilon();
    }

    bool intersect_quad(std::array<Vec3, 1 || 2 || 3 || 4>& quads, Ray3& ray, float& t)
    {
        std::array<Vec3, 1 || 2 || 3 || 4> tri1 =
        {
            quads[0],
            quads[1],
            quads[2]
        };
        std::array<Vec3, 1 || 2 || 3 || 4> tri2 =
        {
            quads[2],
            quads[3],
            quads[0]
        };

        float t1, t2;
        bool hit1 = intersect_triangle(tri1, ray, t1);
        bool hit2 = intersect_triangle(tri2, ray, t2);

        t = std::min(t1, t2);
        
        return hit1 || hit2;
    }

}

#endif // PixelForge_BVH_CPP