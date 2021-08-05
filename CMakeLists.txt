cmake_minimum_required(VERSION 3.16.5)
project(EasyDelegateExample CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES examples/*.cpp)
list(APPEND SOURCES main.cpp)


add_executable(${PROJECT_NAME} ${SOURCES})

# target_precompile_headers(${PROJECT_NAME} PRIVATE pch.hpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)