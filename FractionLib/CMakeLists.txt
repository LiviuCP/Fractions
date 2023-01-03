cmake_minimum_required(VERSION 3.5)

project(FractionLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(FRACTION_LIB_TYPE SHARED)

# errors were encountered when building some libraries as shared on Windows so it has been decided to keep it static on this OS for the moment
if(WIN32)
    set(FRACTION_LIB_TYPE STATIC)
endif()

add_library(FractionLib ${FRACTION_LIB_TYPE}
    fractionlib.cpp
    fraction.cpp
)

target_compile_definitions(FractionLib PRIVATE FRACTIONLIB_LIBRARY)
