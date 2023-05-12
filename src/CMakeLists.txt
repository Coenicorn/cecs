add_subdirectory(cecs)

add_executable(main main.c)

target_compile_options(libcecs PRIVATE -g -Wall -Wpedantic -Werror)

target_link_libraries(main libcecs)