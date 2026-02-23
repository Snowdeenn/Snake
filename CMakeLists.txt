cmake_minimum_required(VERSION 3.15)
project(Snake VERSION 1.0 LANGUAGES C)

set(SOURCES src/main.c src/snake.c src/pomme.c src/jeu.c)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(raylib REQUIRED)

add_executable(Snake ${SOURCES})
target_include_directories(Snake PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(Snake raylib)

add_compile_options(-Wall -Wextra -g)