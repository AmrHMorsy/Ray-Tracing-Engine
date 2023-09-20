cmake_minimum_required(VERSION 3.8)

project(Raytracer)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH /encs/opt/local)

set(CMAKE_CXX_COMPILER /usr/local/opt/llvm/bin/clang++)



set(ENV{EIGEN3_ROOT} /encs/pkg/eigen-3.3.7/root)
set(CMAKE_MODULE_PATH /encs/pkg/eigen-3.3.7/root/cmake)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

include_directories(src/)
include_directories(external/)

aux_source_directory(external SOURCE)
aux_source_directory(src SOURCE)

add_executable(Raytracer ${SOURCE})

find_package(OpenMP COMPONENTS CXX)
if(OpenMP_CXX_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xpreprocessor ${OpenMP_CXX_FLAGS}")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
