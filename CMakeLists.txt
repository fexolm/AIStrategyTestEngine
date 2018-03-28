cmake_minimum_required(VERSION 3.10)
project(StorkEngine)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)

include_directories(include src ${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.c")
file(GLOB HEADERS "include/*.h")

add_executable(StorkEngine main.c ${SOURCES} ${HEADERS})
target_link_libraries(StorkEngine ${SDL2_LIBRARIES})