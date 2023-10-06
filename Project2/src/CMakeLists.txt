cmake_minimum_required(VERSION 3.26)
project(Project2 C)

set(CMAKE_C_STANDARD 17)

add_executable(Project2 main.c
        heap.h
        graph.h
        list.h
        graph_generator.h
        mersenne_twister.h)
