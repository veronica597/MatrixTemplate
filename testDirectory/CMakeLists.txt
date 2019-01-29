

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR,./lib/googletes/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(EXECUTABLE_NAME "runAllTests")

set(TEST_SOURCE_FILES MatrixTests.cpp runAllTests.cpp OperationsTests.cpp)
add_executable(runAllTests ${TEST_SOURCE_FILES} runAllTests.cpp OperationsTests.cpp)
target_link_libraries(runAllTests gtest gtest_main)