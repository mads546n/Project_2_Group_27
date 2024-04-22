cmake_minimum_required(VERSION 3.17)
project(Project_2 C)

set(CMAKE_C_STANDARD 11)

# Add your source files here
set(SOURCE_FILES main.c view/view.c)

add_executable(Project_2 ${SOURCE_FILES})
