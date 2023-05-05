include_directories(${PROJECT_SOURCE_DIR}/include)
set(LIB_SRC myjson.c)
add_library(leptjson ${LIB_SRC})