cmake_minimum_required(VERSION 3.10)
project(YukonCardGame)

set(CMAKE_C_STANDARD 99)

# Add the source files
add_executable(YukonCardGame main.c
        model/model.c
        view/view.c
        controller/controller.c)

# Include directories for each component
target_include_directories(YukonCardGame PRIVATE
        ${PROJECT_SOURCE_DIR}/model
        ${PROJECT_SOURCE_DIR}/view
        ${PROJECT_SOURCE_DIR}/controller)
