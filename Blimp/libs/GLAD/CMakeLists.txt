if(NOT CMAKE_C_COMPILER)
    enable_language(C)
endif()

add_library(GLAD STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c"
)

target_include_directories(GLAD PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set_target_properties(GLAD PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
)
