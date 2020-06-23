cmake_minimum_required(VERSION 3.5)

project(avm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(avm main.cpp abstractvm.cpp token.cpp lexer.cpp)
