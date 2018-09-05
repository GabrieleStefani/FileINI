add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_TEST_FILES test.cpp)
add_executable(test ${SOURCE_TEST_FILES})
target_link_libraries(test gtest gtest_main core)