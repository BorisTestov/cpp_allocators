# Set executables names
set(main "memory_allocator")

# Create list with executables names
set(EXECUTABLES_LIST ${main})

# Set sources
set(SOURCES
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/allocator.cpp
        ${SRC_DIR}/container.cpp

)

# Set headers
set(HEADERS
        ${INCLUDE_DIR}/factorial.h
        ${INCLUDE_DIR}/allocator.h
        ${INCLUDE_DIR}/container.h
)

# Add executables
add_executable(${main} ${SOURCES} ${HEADERS})

foreach(TARGET ${EXECUTABLES_LIST})
    # Include directories
    target_include_directories(${TARGET} PRIVATE "${INCLUDE_DIR}")
    # Set target properties
    set_target_properties(${TARGET} PROPERTIES ${TARGET_PROPERTIES})
    # Link libraries
    target_link_libraries(${TARGET} PRIVATE ${LIBRARIES_LIST})
    # Set compile options
    target_compile_options(${TARGET} PRIVATE ${COMPILE_OPTIONS})
endforeach()

# Install executables
install(TARGETS ${EXECUTABLES_LIST} RUNTIME DESTINATION bin)

