cmake_minimum_required(VERSION 3.28)
project(Project_2 C)

set(CMAKE_C_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/model)
include_directories(${PROJECT_SOURCE_DIR}/view)
include_directories(${PROJECT_SOURCE_DIR}/controller)

add_executable(your_executable_name main.c model/model.c view/view.c controller/controller.c)

