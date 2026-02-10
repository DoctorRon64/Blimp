project(Blimp LANGUAGES C CXX)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(${PROJECT_NAME} SHARED ${SOURCES})
if(MSVC)
    set_property(TARGET ${PROJECT_NAME}
        PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
    )
endif()
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
#target_compile_definitions(${PROJECT_NAME} PUBLIC BLIMP_STATIC)
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC BLIMP_PLATFORM_WINDOWS)
    # Export Dll macro control (for __declspec)
    target_compile_definitions(${PROJECT_NAME} PRIVATE BLIMP_BUILD_DLL)
elseif(UNIX)
    target_compile_definitions(${PROJECT_NAME} PUBLIC BLIMP_PLATFORM_LINUX)
else()
    message(FATAL_ERROR "Blimp only supports Windows and Linux!")
endif()

#Third-party deps
add_subdirectory(libs/spdlog)
add_subdirectory(libs/GLFW)
add_subdirectory(libs/GLAD)
add_subdirectory(libs/imgui)

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC GLAD)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)

#Precompiled headers
target_precompile_headers(${PROJECT_NAME} PRIVATE "src/pch.h")

# TODO Assets Folder
# add_dependencies(${PROJECT_NAME} copyAssets)
# add_custom_target(copyAssets
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${CMAKE_CURRENT_SOURCE_DIR}/assets
#         ${CMAKE_CURRENT_SOURCE_DIR}/build/assets/
# )
