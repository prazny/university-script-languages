cmake_minimum_required(VERSION 3.21)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(ExitCode ExitCode.cpp)
add_executable(Head Head.cpp)
add_executable(Paths ../cpp-helpers/Paths.cpp)
add_executable(Process Process.cpp)
add_executable(ShowAll ShowAll.cpp)
add_executable(ShowSimilar ShowSimilar.cpp)
add_executable(Tail Tail.cpp)

add_executable(Aggregate L3Z1/main.cpp)
