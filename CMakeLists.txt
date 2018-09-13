cmake_minimum_required(VERSION 3.12)
project(FileINI)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)
set(SOURCE_FILES INIManager.cpp INIManager.h NotFoundException.h)

add_executable(FileINI main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(FileINI core)