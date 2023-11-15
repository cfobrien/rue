cmake_minimum_required(VERSION 3.27)

project(rue VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

include_directories(src test)


add_executable(
	rue
	src/main.cpp
)


enable_testing()

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/b10fad38c4026a29ea6561ab15fc4818170d1c10.zip
)

FetchContent_MakeAvailable(googletest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test)

add_executable(
	hello_test
	test/hello_test.cc
)

target_link_libraries(
	hello_test
	gtest_main
)

add_test(
	NAME test/hello_test
	COMMAND hello_test
)
