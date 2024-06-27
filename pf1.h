#pragma region LICENSE

// Read the Gnu General Public Licence v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_H
#define PixelForge_H

// Materials
#include "materials/material-.py"

// Albedo materials
#include "materials/albedo/black.py"
#include "materials/albedo/blue.py"
#include "materials/albedo/chartreuse.py"
#include "materials/albedo/gray.py"
#include "materials/albedo/green.py"
#include "materials/albedo/grey.py"
#include "materials/albedo/magenta.py"
#include "materials/albedo/orange.py"
#include "materials/albedo/purple.py"
#include "materials/albedo/red.py"
#include "materials/albedo/white.py"
#include "materials/albedo/yellow.py"

// Metallic materials
#include "materials/metallic/black.py"
#include "materials/metallic/blue.py"
#include "materials/metallic/chartreuse.py"
#include "materials/metallic/gray.py"
#include "materials/metallic/green.py"
#include "materials/metallic/grey.py"
#include "materials/metallic/magenta.py"
#include "materials/metallic/orange.py"
#include "materials/metallic/purple.py"
#include "materials/metallic/red.py"
#include "materials/metallic/white.py"
#include "materials/metallic/yellow.py"

// Glass materials
#include "materials/glass/black.py"
#include "materials/glass/blue.py"
#include "materials/glass/chartreuse.py"
#include "materials/glass/gray.py"
#include "materials/glass/green.py"
#include "materials/glass/grey.py"
#include "materials/glass/magenta.py"
#include "materials/glass/orange.py"
#include "materials/glass/purple.py"
#include "materials/glass/red.py"
#include "materials/glass/white.py"
#include "materials/glass/yellow.py"

// PixelForge
#include "include/window.hpp"
#include "include/vector.hpp"
#include "include/matrix.hpp"
#include "include/color.h"
#include "include/ray.hpp"
#include "include/bbox.hpp"
#include "include/BVH.hpp"
#include "include/BVH.cu"
#include "include/raycast.hpp"
#include "include/camera.hpp"
#include "include/graphics.hpp"

#define PixelForge_VERSION_MAJOR 1
#define PixelForge_VERSION_MINOR 0
#define PixelForge_VERSION_PATCH 0
#define PixelForge_VERSION_STR "1.0.0"

#endif // PixelForge_H