cmake_minimum_required(VERSION 3.5)

project(FractionTests LANGUAGES CXX)

add_definitions(-DGTEST_LANGUAGE_CXX11)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Threads REQUIRED)

set(UserProvidedGTestDir "../../googletest")

if ($ENV{GOOGLETEST_DIR})
    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    if (NOT ${UserProvidedGTestDir} STREQUAL "")
        message(WARNING "Using user provided src dir")
    endif ()
    set(GOOGLETEST_DIR ${UserProvidedGTestDir})
endif ()

if (EXISTS ${GOOGLETEST_DIR})
    set(GTestSrc ${GOOGLETEST_DIR}/googletest)
    set(GMockSrc ${GOOGLETEST_DIR}/googlemock)
elseif (UNIX AND EXISTS /usr/src/gtest)
    set(GTestSrc /usr/src/gtest)
    message(WARNING "Using gtest from system")
    if (EXISTS /usr/src/gmock)
        set(GMockSrc /usr/src/gmock)
    endif ()
else ()
    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)

if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
endif ()

include_directories(${GTestIncludes}
                    ../FractionLib)

add_executable(FractionTests main.cpp
               ${GTestFiles})

add_test(NAME FractionTests COMMAND FractionTests)

target_link_libraries(FractionTests PRIVATE Threads::Threads)
target_link_libraries(FractionTests PRIVATE FractionLib)

