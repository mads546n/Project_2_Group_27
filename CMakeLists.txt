cmake_minimum_required(VERSION 3.10)  # Specify the minimum version of CMake.

# Set the project name and the C standard
project(Project_2_Group_27)
set(CMAKE_C_STANDARD 99)  # Use C99 standard.

# Add the executable target
add_executable(main
        main.c
        model/model.c
        controller/controller.c
        view/view.c)

# Include directories
include_directories(
        ${PROJECT_SOURCE_DIR}/model
        ${PROJECT_SOURCE_DIR}/controller
        ${PROJECT_SOURCE_DIR}/view
)

# Uncomment the following line if you have external libraries to link
# target_link_libraries(main name_of_library)
