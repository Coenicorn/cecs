cmake_minimum_required(VERSION 3.22)

project(cecs)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(warnings "-Wall -Wextra -Werror")

add_subdirectory(src)