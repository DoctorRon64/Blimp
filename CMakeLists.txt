cmake_minimum_required(VERSION 3.25)
project(projects LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#external libs
add_subdirectory(external/spdlog)

add_subdirectory(Blimp)
add_subdirectory(Sandbox)