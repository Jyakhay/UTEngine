cmake_minimum_required(VERSION 3.25)
project(UTEngine)

set(CMAKE_CXX_STANDARD 20)
set(UTENGINE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Binaries/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Binaries/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Binaries/)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_definitions(COMPILER_MSVC)
elif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_definitions(COMPILER_CLANG)
elif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_definitions(COMPILER_GNU)
endif()

add_subdirectory(Dependencies)
add_subdirectory(Engine)
add_subdirectory(Testing)