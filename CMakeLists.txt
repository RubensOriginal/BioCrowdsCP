cmake_minimum_required(VERSION 3.31)
project(BioCrowdsCP C)

set(CMAKE_C_STANDARD 11)

add_executable(BioCrowdsCP main.c
        world.c
        world.h
        Vector3.c
        Vector3.h
        Marker.c
        Marker.h
        Cell.h
        Cell.c
        Agent.h
        Agent.c)
