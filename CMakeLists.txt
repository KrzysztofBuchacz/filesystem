cmake_minimum_required(VERSION 2.8.8)

set(MODULE_NAME filesystem)
project(${MODULE_NAME})

if(UNIX)
    add_definitions(-std=c++11)
endif(UNIX)

add_library(${MODULE_NAME} STATIC kbu/filesystem.h kbu/filesystem.cpp)
