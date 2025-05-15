add_executable(infix-to-postfix
        src/main.cpp
        src/Token.cpp
        src/Lexer.cpp
        src/Parser_RPN.cpp)
target_include_directories(infix-to-postfix PRIVATE include)
