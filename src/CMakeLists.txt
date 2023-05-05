include_directories(${PROJECT_SOURCE_DIR}/include)

set(APP_SRC test.c)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)

add_executable(test ${APP_SRC})
target_link_libraries(test leptjson)