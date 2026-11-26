cmake_minimum_required(VERSION 3.20)

project(TKI242Task2Variant22 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(kindergarten_library STATIC
    src/KindergartenPerson.cpp
    src/Child.cpp
    src/Educator.cpp
    src/Activity.cpp
    src/Kindergarten.cpp
)
target_include_directories(kindergarten_library PUBLIC include)

add_executable(kindergarten_app src/main.cpp)
target_link_libraries(kindergarten_app PRIVATE kindergarten_library)

include(CTest)
if(BUILD_TESTING)
    find_package(GTest CONFIG QUIET)
    if(NOT GTest_FOUND)
        include(FetchContent)
        if(POLICY CMP0135)
            cmake_policy(SET CMP0135 NEW)
        endif()
        FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
        )
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
    endif()

    add_executable(kindergarten_tests tests/Tests.cpp)
    target_link_libraries(kindergarten_tests PRIVATE kindergarten_library GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(kindergarten_tests)
endif()

foreach(target kindergarten_library kindergarten_app kindergarten_tests)
    if(TARGET ${target})
        if(MSVC)
            target_compile_options(${target} PRIVATE /W4 /permissive- /utf-8)
        else()
            target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
        endif()
    endif()
endforeach()
