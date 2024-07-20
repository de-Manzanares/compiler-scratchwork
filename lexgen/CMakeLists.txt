set(CMAKE_CXX_STANDARD 23)

add_executable(lexgen
        main.cpp
        Lexer_Generator.cpp
        Token.cpp
        Lexer.cpp
        Parser_lexgen.cpp)
target_include_directories(lexgen PRIVATE .)

add_executable(lexgen-test lexer.cpp)