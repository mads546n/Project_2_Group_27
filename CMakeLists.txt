cmake_minimum_required(VERSION 3.10)
project(Project_2)

set(CMAKE_C_STANDARD 99)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(Project_2 main.c
        model/model.c
        view/view.c
        controller/controller.c
        card/card.c)  # Include this if you have implementations in card.c

# Link any libraries if needed
# target_link_libraries(Project_2 ...)
