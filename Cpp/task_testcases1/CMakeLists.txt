cmake_minimum_required(VERSION 3.10)
project(PruebaParalaje)

# Activamos C++17
set(CMAKE_CXX_STANDARD 17)

# Incluimos Eigen (si está instalado en una ubicación estándar)
find_package(Eigen3 3.3 REQUIRED)

# Incluir Sophus
find_package(Sophus REQUIRED)

# Incluir Google Test
find_package(GTest REQUIRED)

# Añadir el archivo fuente
add_executable(prueba_paralaje prueba_paralaje.cpp)

# Enlazamos las bibliotecas necesarias
target_link_libraries(prueba_paralaje Eigen3::Eigen Sophus::Sophus GTest::GTest GTest::Main pthread)
