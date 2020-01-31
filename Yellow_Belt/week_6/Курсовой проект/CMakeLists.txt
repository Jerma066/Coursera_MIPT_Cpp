cmake_minimum_required(VERSION 3.15)
project(_)

set(CMAKE_CXX_STANDARD 17)

add_executable(_ main.cpp token.cpp token.h condition_parser.cpp condition_parser.h date.cpp date.h database.cpp database.h node.cpp node.h condition_parser_test.cpp test_runner.h)