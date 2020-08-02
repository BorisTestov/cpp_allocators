# Set patch value. It's not 0 if build on Travis
set(PATCH "0")
if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(PATCH $ENV{TRAVIS_BUILD_NUMBER})
endif()

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
