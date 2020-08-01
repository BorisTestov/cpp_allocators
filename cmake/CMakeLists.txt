cmake_minimum_required(VERSION 3.2)

# Set patch value. It's not 0 if build on Travis
set(PATCH "0")
if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(PATCH $ENV{TRAVIS_BUILD_NUMBER})
endif()

project(memory_allocator VERSION 0.0.${PATCH})

# Set automoc for QTest
set(CMAKE_AUTOMOC ON)
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(SRC_DIR ${PROJECT_ROOT}/src)
set(INCLUDE_DIR ${PROJECT_ROOT}/include)
set(TARGET_PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

# Set compile options
set(COMPILE_OPTIONS -Wall -Wextra -pedantic -Werror)
if (MSVC)
    set(COMPILE_OPTIONS /W4)
endif()

find_package(Qt5 REQUIRED COMPONENTS Widgets Test)

# Configure file with current app version
configure_file(${PROJECT_ROOT}/include/version.h.in
               ${PROJECT_ROOT}/include/version.h)

# Set up libraries
include(${CMAKE_CURRENT_SOURCE_DIR}/libraries/libraries.cmake)

# Set up and install executables
include(${CMAKE_CURRENT_SOURCE_DIR}/executables/executables.cmake)

# Set up CPack
include(${CMAKE_CURRENT_SOURCE_DIR}/cpack/cpack.cmake)

# Enable testing
include(${CMAKE_CURRENT_SOURCE_DIR}/tests/tests.cmake)
