cmake_minimum_required(VERSION 3.31)
project(BioCrowdsCP CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Procura OpenMP
find_package(OpenMP REQUIRED)

add_executable(BioCrowdsCP
        main.cpp
        World.cpp
        world.h
        Vector3.cpp
        Vector3.h
        Marker.cpp
        Marker.h
        Cell.cpp
        Cell.h
        Agent.cpp
        Agent.h
)

# Liga o OpenMP ao alvo
target_link_libraries(BioCrowdsCP PRIVATE OpenMP::OpenMP_CXX)
