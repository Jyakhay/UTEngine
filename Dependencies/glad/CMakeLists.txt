cmake_minimum_required(VERSION 3.25)

set(GLAD_SOURCES
    "include/glad/glad.h"
    "include/KHR/khrplatform.h"
    "src/glad.c"
)

add_library(glad ${GLAD_SOURCES})
target_include_directories(glad PRIVATE "include")