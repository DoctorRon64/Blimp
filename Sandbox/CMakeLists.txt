project(Sandbox LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/SandboxApp.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Blimp)

if (MINGW)
  target_link_options(${PROJECT_NAME} PRIVATE -mconsole)
endif()