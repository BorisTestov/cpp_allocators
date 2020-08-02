find_package(Qt5 REQUIRED COMPONENTS Test)

set(TESTS_INCLUDE_DIR ${INCLUDE_DIR}/tests)
set(TESTS_SRC_DIR ${SRC_DIR}/tests)

# Add tests names
set(memory_allocator_test_executable "memory_allocator_test")

# Add tests executables
add_executable(${memory_allocator_test_executable} ${TESTS_SRC_DIR}/main_test.cpp)

# Create list with tests names
set(TESTS_LIST ${memory_allocator_test_executable})

foreach(TARGET ${TESTS_LIST})
    # Set target properties
    set_target_properties(${TARGET} PROPERTIES ${TARGET_PROPERTIES})
    # Include directories
    target_include_directories(${TARGET} PRIVATE ${INCLUDE_DIR} ${TESTS_INCLUDE_DIR})
    # Link libraries
    target_link_libraries(${TARGET} PRIVATE ${LIBRARIES_LIST} Qt5::Test)
    # Set compile options
    target_compile_options(${TARGET} PRIVATE ${COMPILE_OPTIONS})
endforeach()

enable_testing()
foreach(TESTNAME ${TESTS_LIST})
    add_test(${TESTNAME} ${TESTNAME})
endforeach()
