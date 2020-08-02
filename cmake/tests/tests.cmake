find_package(Qt5 REQUIRED COMPONENTS Test)

set(TESTS_INCLUDE_DIR ${INCLUDE_DIR}/tests)
set(TESTS_SRC_DIR ${SRC_DIR}/tests)

# Add tests
set(main_test "memory_allocator_test")

# Add tests executables
add_executable(${main_test} ${TESTS_SRC_DIR}/main_test.cpp ${TESTS_INCLUDE_DIR}/main_test.h)

# Create list with tests names
set(TESTS_LIST ${main_test})

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
