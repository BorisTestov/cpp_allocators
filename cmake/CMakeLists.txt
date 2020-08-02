cmake_minimum_required(VERSION 3.2)

# Set up parameters
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_config.cmake)

project(memory_allocator VERSION 0.0.${PATCH})

# Set up libraries
include(${CMAKE_CURRENT_SOURCE_DIR}/libraries/libraries.cmake)

# Set up and install executables
include(${CMAKE_CURRENT_SOURCE_DIR}/executables/executables.cmake)

# Set up CPack
include(${CMAKE_CURRENT_SOURCE_DIR}/cpack/cpack.cmake)

# Enable testing
include(${CMAKE_CURRENT_SOURCE_DIR}/tests/tests.cmake)
