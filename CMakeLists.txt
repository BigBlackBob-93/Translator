cmake_minimum_required(VERSION 3.23)
project(Translator)
set(CMAKE_CXX_STANDARD 14)
add_executable(Translator main.cpp Lexer.cpp Lexer.h Parser.h Parser.cpp Interpreter.cpp Interpreter.h)