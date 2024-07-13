cmake_minimum_required(VERSION 3.26)
project(olymp_gcc)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DLOCAL)
include_directories(.)
add_executable(olymp_gcc sol.cpp)
