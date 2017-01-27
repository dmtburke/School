cmake_minimum_required(VERSION 3.3)
project(ucd_csci2312_pa0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.cpp)

add_executable(ucd_csci2312_pa0 ${SOURCE_FILES})