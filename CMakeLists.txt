cmake_minimum_required(VERSION 3.5)

project(Fractions LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(FractionLib)
add_subdirectory(FractionTests)
