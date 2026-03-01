project(Sandbox LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/SandboxApp.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Blimp)

if (MINGW)
  target_link_options(${PROJECT_NAME} PRIVATE -mconsole)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/Blimp/src")
target_precompile_headers(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/Blimp/src/pch.h")
