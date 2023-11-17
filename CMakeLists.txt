cmake_minimum_required(VERSION 3.27)

project(rue VERSION 1.0)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

include_directories(src test)
add_subdirectory(lib/googletest)


add_executable(
	rue
	src/main.cpp
)

enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test)

add_executable(
	hello_test
	test/hello_test.cc
)

target_link_libraries(
	hello_test
  PUBLIC
  gtest
)

add_test(
	NAME test/hello_test
	COMMAND hello_test
)
