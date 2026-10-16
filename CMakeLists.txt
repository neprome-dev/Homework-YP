cmake_minimum_required(VERSION 3.20)

project(TKI242Variant22 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(MATRIX_LIBRARY_SOURCES
    src/Generator.cpp
    src/ConstantGenerator.cpp
    src/ZeroGenerator.cpp
    src/RandomGenerator.cpp
    src/IStreamGenerator.cpp
    src/Matrix.cpp
    src/Exercise.cpp
    src/Task1.cpp
    src/Task2.cpp
)

add_library(matrix_library STATIC ${MATRIX_LIBRARY_SOURCES})
target_include_directories(matrix_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(matrix_app src/main.cpp)
target_link_libraries(matrix_app PRIVATE matrix_library)

foreach(target matrix_library matrix_app)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endforeach()

include(CTest)
if(BUILD_TESTING)
    find_package(GTest CONFIG QUIET)

    if(NOT GTest_FOUND)
        include(FetchContent)
        FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        )
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
    endif()

    add_executable(matrix_tests tests/Tests.cpp)
    target_link_libraries(matrix_tests PRIVATE matrix_library GTest::gtest_main)

    if(MSVC)
        target_compile_options(matrix_tests PRIVATE /W4 /permissive-)
    else()
        target_compile_options(matrix_tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()

    include(GoogleTest)
    gtest_discover_tests(matrix_tests)
endif()
