cmake_minimum_required(VERSION 3.28.1)
project(Expression_Evaluator_Prz)

set(CMAKE_CXX_STANDARD 20)

add_executable(Expression_Evaluator_Prz src/main.cpp
        src/core/Calculator.h
        src/core/Calculator.cpp
        src/core/Token.cpp
        src/core/Token.h)
