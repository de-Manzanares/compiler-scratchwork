cmake_minimum_required(VERSION 3.28)
project(Hatchling)

set(CMAKE_CXX_STANDARD 23)

add_executable(hatchling
        infix_to_postfix_translator/src/main.cpp
        infix_to_postfix_translator/src/Token.cpp
        infix_to_postfix_translator/src/Lexer.cpp
        infix_to_postfix_translator/src/Parser_RPN.cpp)
target_include_directories(hatchling PRIVATE infix_to_postfix_translator/include)

add_subdirectory(lexgen)
