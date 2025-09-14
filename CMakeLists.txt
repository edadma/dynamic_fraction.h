cmake_minimum_required(VERSION 3.10)
project(dynamic_fraction C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Primary executable - Unit tests with Unity
add_executable(tests
    tests.c
    devDeps/unity/unity.c
)

# Enable Unity double precision support
target_compile_definitions(tests PRIVATE UNITY_INCLUDE_DOUBLE)

# Include directories for tests
target_include_directories(tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/devDeps
    ${CMAKE_CURRENT_SOURCE_DIR}/devDeps/unity
)

# Link math library
target_link_libraries(tests m)

# Example executable using main.c
add_executable(example main.c)
target_include_directories(example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(example m)

# Enable testing
enable_testing()
add_test(NAME FractionTests COMMAND tests)
