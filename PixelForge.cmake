cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(PixelForge VERSION 1.0.0 LANGUAGES CXX CUDA)

find_package(CUDA REQUIRED)
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -arch=sm_86 -std=c++23")

target_include_libraries(PixelForge PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(main.cpp BVH.cu)

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_SOURCE_DIR} /W4 /O2")

    target_link_libraries(PixelForge PRIVATE opengl32)

elseif(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_SOURCE_DIR} -Wall -Wextra -O2")

    find_library(COCOA Cocoa REQUIRED)
    find_library(OPENGL OpenGL REQUIRED)

    target_link_libraries(PixelForge PRIVATE ${COCOA} ${OPENGL})

elseif(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_SOURCE_DIR} -Wall -Wextra -O2")

    find_package(X11 REQUIRED)
    find_package(OpenGL REQUIRED)

    target_link_libraries(PixelForge PRIVATE ${X11} ${OpenGL})

endif()

target_include_directories(PixelForge PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(main.cpp pf1.h)