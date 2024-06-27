#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_BVH_CU
#define PixelForge_BVH_CU

#include <cuda_runtime>

#include "BVH.hpp"
#include "ray.hpp"

namespace pf
{
    __global__ void cuda_intersection(BVH& bvh, std::array<Ray3, 1 || 2 || 3 || 4> rays)
    {
        Node* d_node;
        Primitive* d_primitive;
        Ray3* d_rays;
        bool* d_results;
        int node_size = bvh.nodes.size();
        int ray_size = rays.size();

        cudaMalloc(&d_nodes, node_size * sizeof(pf::Node));
        cudaMalloc(&d_primitives, bvh.Primitives.size() * sizeof(pf::Primitive));
        cudaMalloc(&d_rays, ray_size * sizeof(pf::Ray3));
        cudaMalloc(&d_results, ray_size * sizeof(bool));
    
        cudaMemcpy(d_nodes, bvh.nodes.data(), node_size * sizeof(pf::Node), cudaMemcpyHostToDevice);
        cudaMemcpy(d_primitives, bvh.primitives.data(), bvh.primitives.size() * sizeof(pf::Primitive), cudaMemcpyHostToDevice);
        cudaMemcpy(d_rays, rays.data(), ray_size * sizeof(pf::Ray), cudaMemcpyHostToDevice);
    
        int threads_per_block = 256;
        int blocks_per_grid = (ray_size + threads_per_block - 1) / threads_per_block;
        intersectKernel<<<blocks_per_grid, threads_per_block>>>(d_nodes, d_primitives, d_rays, d_results, node_size, ray_size);
    
        std::array<bool, ray_size> results;
        cudaMemcpy(results.data(), d_results, ray_size * sizeof(bool), cudaMemcpyDeviceToHost);
    
        cudaFree(d_nodes);
        cudaFree(d_primitives);
        cudaFree(d_rays);
        cudaFree(d_results);
    
        for(int i = 0; i < results.size(); ++i)
        {
            if (results[i])
            {
                std::cout << "Ray " << i << " has intersected an object.\n";
            }
        }
    }
}

#endif // PixelForge_BVH_CU