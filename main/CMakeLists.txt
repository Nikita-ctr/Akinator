cmake_minimum_required(VERSION 3.25)
project(akinator C)

set(CMAKE_C_STANDARD 99)

add_executable(akinator main.c)

target_link_libraries(akinator lib)