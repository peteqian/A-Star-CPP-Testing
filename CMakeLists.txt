cmake_minimum_required(VERSION 3.8)

set(This Simulation)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
    ass2-refactor.h
    ass3-refactor.h
)

set(Sources
    ass2-refactor.cpp
    ass3-refactor.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)