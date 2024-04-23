cmake_minimum_required(VERSION 3.28)
project(Project_2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Project_2 main.c
        controller/controller.c
        model/model.c
        view/view.c
        view/view.h
        controller/controller.h
        model/model.h
        model/card.c
        model/card.h
)
