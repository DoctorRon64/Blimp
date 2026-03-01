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
# ImGui (no upstream CMakeLists, define target manually)
add_library(imgui
    libs/imgui/imgui.cpp
    libs/imgui/imgui_draw.cpp
    libs/imgui/imgui_tables.cpp
    libs/imgui/imgui_widgets.cpp
    libs/imgui/imgui_demo.cpp    

    # backends (for GLFW + OpenGL3)
    libs/imgui/backends/imgui_impl_glfw.cpp
    libs/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui" "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends")

target_link_libraries(imgui PUBLIC glfw GLAD)
target_compile_definitions(imgui PRIVATE GLFW_INCLUDE_NONE)

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
