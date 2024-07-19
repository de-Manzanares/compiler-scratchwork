cmake_minimum_required(VERSION 3.28)
project(Hatchling)

set(CMAKE_CXX_STANDARD 23)

add_executable(hatchling
        src/main.cpp
        src/Token.cpp
        src/Lexer.cpp
        src/Parser_RPN.cpp)
target_include_directories(hatchling PRIVATE include)

