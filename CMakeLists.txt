cmake_minimum_required(VERSION 3.12)
project(FileINI)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)

add_executable(FileINI main.cpp INIManager.cpp INIManager.h test/test.cpp)