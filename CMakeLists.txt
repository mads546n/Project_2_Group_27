cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(YukonGame VERSION 1.0 DESCRIPTION "Yukon card game implemented in C using MVC structure")

# Specify the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add executable
add_executable(YukonGame main.c model.c view.c controller.c)

# Include directories
target_include_directories(YukonGame PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}"
)
