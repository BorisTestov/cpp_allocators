# Set executables names
set(memory_allocator_executable "memory_allocator")

# Add executables
add_executable(${memory_allocator_executable}
                ${SRC_DIR}/main.cpp)

# Create list with executables names
set(EXECUTABLES_LIST ${memory_allocator_executable})

foreach(TARGET ${EXECUTABLES_LIST})
    # Include directories
    target_include_directories(${TARGET} PRIVATE "${INCLUDE_DIR}")
    # Set target properties
    set_target_properties(${TARGET} PROPERTIES ${TARGET_PROPERTIES})
    # Link libraries
    target_link_libraries(${TARGET} PRIVATE ${LIBRARIES_LIST} Qt5::Widgets)
    # Set compile options
    target_compile_options(${TARGET} PRIVATE ${COMPILE_OPTIONS})
endforeach()

# Install executables
install(TARGETS ${EXECUTABLES_LIST} RUNTIME DESTINATION bin)

