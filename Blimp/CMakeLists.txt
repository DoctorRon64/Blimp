project(Blimp LANGUAGES CXX)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

if (CMAKE_SIZEOF_VOID_P)
target_compile_definitions(${PROJECT_NAME} PUBLIC BLIMP_PLATFORM_WINDOWS)
elseif(UNIX)
target_compile_definitions(${PROJECT_NAME} PUBLIC BLIMP_PLATFORM_LINUX)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

# for dll libs
# add_library(Blimp SHARED ${SOURCES})
#target_compile_definitions(Blimp PRIVATE BLIMP_BUILD_DLL)

# TODO Precompiled headers!!!
# target_precompile_headers(${PROJECT_NAME} PRIVATE "src/Precompiled.h")

# TODO Assets Folder
# add_dependencies(${PROJECT_NAME} copyAssets)
# add_custom_target(copyAssets
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${CMAKE_CURRENT_SOURCE_DIR}/assets
#         ${CMAKE_CURRENT_SOURCE_DIR}/build/assets/
# )
