cmake_minimum_required(VERSION 3.25)
project(BlimpEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Keep all binaries in a single, predictable layout across generators.
set(BLIMP_OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(BLIMP_LIBRARY_DIR "${CMAKE_BINARY_DIR}/lib")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BLIMP_OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BLIMP_OUTPUT_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BLIMP_LIBRARY_DIR}")

if (CMAKE_CONFIGURATION_TYPES)
    foreach(cfg ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER "${cfg}" cfg_upper)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${cfg_upper} "${BLIMP_OUTPUT_DIR}/${cfg}")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${cfg_upper} "${BLIMP_OUTPUT_DIR}/${cfg}")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${cfg_upper} "${BLIMP_LIBRARY_DIR}/${cfg}")
    endforeach()
endif()

add_subdirectory(Blimp)
add_subdirectory(Sandbox)

# maybe delete this
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(Blimp PROPERTIES FOLDER "Blimp")
set_target_properties(Sandbox PROPERTIES FOLDER "Sandbox")