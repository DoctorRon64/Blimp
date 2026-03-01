project(Sandbox LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/Main.cpp src/SandboxApp.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Blimp)

if (MINGW)
  target_link_options(${PROJECT_NAME} PRIVATE -mconsole)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/Blimp/src")
target_precompile_headers(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/Blimp/src/pch.h")

if (MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wshadow)
endif()

if (BLIMP_ENABLE_SANITIZERS AND NOT MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
  target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)
endif()
