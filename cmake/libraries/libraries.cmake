# Set libraries names
set(version_library "version")
set(allocator_library "allocator")

# Add libraries
add_library(${version_library} ${SRC_DIR}/version.cpp)
add_library(${allocator_library} ${SRC_DIR}/allocator.cpp)
add_dependencies(${allocator_library} Qt5::Widgets)

# Create list with libraries names
set(LIBRARIES_LIST ${version_library} ${allocator_library})

foreach(TARGET ${LIBRARIES_LIST})
    #Include directories
    target_include_directories(${TARGET} PRIVATE "${INCLUDE_DIR}")
    # Set target properties
    set_target_properties(${TARGET} PROPERTIES ${TARGET_PROPERTIES})
    # Set compile options
    target_compile_options(${TARGET} PRIVATE ${COMPILE_OPTIONS})
endforeach()


