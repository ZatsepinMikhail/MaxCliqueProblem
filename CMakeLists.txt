cmake_minimum_required(VERSION 3.3)
project(MaxCliqueProblem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp AlgorithmMC.cpp AlgorithmMC.h AlgorithmMCQ.cpp AlgorithmMCQ.h)
add_executable(MaxCliqueProblem ${SOURCE_FILES})