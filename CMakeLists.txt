cmake_minimum_required(VERSION 3.26)
project(olymp_gcc)

set(CMAKE_CXX_STANDARD 23)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftrapv")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLO")
endif()
add_executable(olymp_gcc sol.cpp)
