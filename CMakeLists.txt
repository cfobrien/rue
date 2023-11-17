cmake_minimum_required(VERSION 3.27)

project(rue VERSION 1.0)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

include_directories(src test)
link_directories(src)
add_subdirectory(lib/googletest)


add_executable(
	rue
	src/main.cpp
    src/rue_tokenizer.cpp
    src/rue_error.cpp
    src/rue_file_utils.cpp
)

enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test)

add_executable(
	tokenizer_test
    test/main.cpp
	test/tokenizer_test.cc
)

target_link_libraries(
	tokenizer_test
    PUBLIC
    gtest
)

add_test(
	NAME test/tokenizer_test
	COMMAND tokenizer_test
)
