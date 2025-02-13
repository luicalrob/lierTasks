cmake_minimum_required(VERSION 3.10)
project(Finanzas)

# Incluir Google Test
find_package(GTest REQUIRED)

# Activar C++17
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR})

# Ejecutable principal
add_executable(finanzas main.cpp finanzas.cpp)

# Crear los tests
add_executable(finanzas_test finanzas_test.cpp finanzas.cpp)

target_link_libraries(finanzas_test gtest gtest_main pthread)
