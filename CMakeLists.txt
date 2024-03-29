cmake_minimum_required(VERSION 3.10)

# Set the project name
project(LeptJsonTests)

set(CMAKE_SUPPRESS_REGENERATION true)

# Specify C++ standard
set(C_STANDARD 11)

# Add include directories
include_directories(include)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)
# Set library output path
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# Find source files
file(GLOB SOURCES "src/*.c" "include/*.c")

# Add executable target with source files
add_executable(test ${SOURCES})
#add debug
target_compile_options(test PUBLIC -g)

# Create and install library
add_library(leptjson STATIC include/leptjson.c)
install(TARGETS leptjson 
        DESTINATION ${CMAKE_SOURCE_DIR}/lib)

# Link the library to the executable
target_link_libraries(test leptjson)
