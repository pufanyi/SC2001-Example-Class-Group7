cmake_minimum_required(VERSION 3.26)
project(Project1 C)

set(CMAKE_C_STANDARD 11)

add_executable(Project1 main.c
        test_case_generator.h
        evaluate.h
        sort.h
        "mersenne_twister.h"
)
