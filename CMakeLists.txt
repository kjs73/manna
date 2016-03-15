cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_COMPILER "c++")
set(CMAKE_CXX_FLAGS "-std=c++0x")
add_executable(manna manna_main.cpp manna.cpp)
