cmake_minimum_required (VERSION 2.6)
project (leptjson_test C)

set(CMAKE_C_COMPILER "F:/TDM-GCC-64/bin/gcc.exe")

include_directory(${PROJECT_SOURCE_DIR}/include)
set(SRC "./src/myjson.c ./src/test.c")

add_library(leptjson myjson.c)
add_executable(leptjson_test test.c)
target_link_libraries(leptjson_test leptjson)