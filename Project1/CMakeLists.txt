cmake_minimum_required(VERSION 3.26)
project(Project1 C)

set(CMAKE_C_STANDARD 11)

add_executable(Project1 main.c
        test_case_generator.h
        test_case_generator.c
        insertion_sort.c
        insertion_sort.h
        merge_sort.c
        merge_sort.h
)
