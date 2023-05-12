cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(libcecs VERSION 1.0.0)

add_library(libcecs STATIC
    ecs.c
)

target_compile_options(libcecs PRIVATE -g -Wall -Wpedantic -Werror)

target_include_directories(libcecs PUBLIC ./include)