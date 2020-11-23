cmake_minimum_required(VERSION 3.0.0)
project(chess)

include_directories(include)
file(GLOB_RECURSE SOURCES src/*.cc)

add_executable(chess ${SOURCES})