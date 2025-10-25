cmake_minimum_required(VERSION 3.14)
project(lab3 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# Подключаем заголовки
include_directories(include)

# Библиотека фигур
add_library(figures STATIC
    src/Figure.cpp
    src/diamond.cpp
    src/hexagon.cpp
    src/pentagon.cpp
)

# Основная программа
add_executable(lab3_main main.cpp)
target_link_libraries(lab3_main figures)

# Тесты (если нужны)
find_package(GTest REQUIRED)
add_executable(run_tests tests/tests.cpp)
target_link_libraries(run_tests figures GTest::gtest GTest::gtest_main)