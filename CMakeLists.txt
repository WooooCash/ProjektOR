cmake_minimum_required(VERSION 3.27)
project(ProjektOR)

set(CMAKE_CXX_STANDARD 17)

add_executable(ProjektOR main.cpp
        main.cpp
        linmath.h
        QuadTree.cpp
        QuadTree.h)

find_package(assimp CONFIG REQUIRED)
target_link_libraries(ProjektOR PRIVATE assimp::assimp)