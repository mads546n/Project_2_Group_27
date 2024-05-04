cmake_minimum_required(VERSION 3.28)
project(Project_2 C)

set(CMAKE_C_STANDARD 11)

# Specify the executable and all the source files it depends on
add_executable(Project_2
        main.c
        controller/controller.c
        model/model.c
        view/view.c
)

# Set include directories to allow all source files to include headers correctly
include_directories(
        ${PROJECT_SOURCE_DIR}/model
        ${PROJECT_SOURCE_DIR}/controller
        ${PROJECT_SOURCE_DIR}/view
)
