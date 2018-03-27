cmake_minimum_required(VERSION 3.10)
project(AIStrategyTestEngine)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)

include_directories(AIStrategyTestEngine ${SDL2_INCLUDE_DIRS})

add_executable(AIStrategyTestEngine main.c)
target_link_libraries(AIStrategyTestEngine ${SDL2_LIBRARIES})