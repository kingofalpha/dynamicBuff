cmake_minimum_required(VERSION 3.17)
project(maloc)

set(CMAKE_CXX_STANDARD 14)

add_executable(maloc main.cpp dynamicStore.c dynamicStore.h)