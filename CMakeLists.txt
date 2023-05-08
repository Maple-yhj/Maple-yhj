cmake_minimum_required(VERSION 3.10)

# Set the project name
project(LeptJsonTests)

# Specify C++ standard
set(CMAKE_C_STANDARD 11)

# Add include directories
include_directories(include)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

# Find source files
file(GLOB SOURCES "src/*.c" "include/*.c")

# Add executable target with source files
add_executable(test ${SOURCES})

# Add library path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Create and install library
add_library(leptjson STATIC include/leptjson.c)
install(TARGETS leptjson DESTINATION lib)

# Link the library to the executable
target_link_libraries(test leptjson)
