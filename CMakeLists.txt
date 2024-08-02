cmake_minimum_required(VERSION 3.29.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIED True)
set(CMAKE_CXX_EXTENTIONS False)

project(PixelForge VERSION 1.0.0 LANGUAGES C CXX CUDA)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES src/*.cpp, src/*.inl)
file(GLOB BIN "*.a")

add_executable(HYDRAlib ${BIN})

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/toolchain.cmake")

find_package(PKG_CONFIG REQUIRED)

add_definitions(-D_GNU_SOURCE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++23 -fPIC")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu23 -fPIC")
