cmake_minimum_required(VERSION 3.10)
project(gserver)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(network)
add_subdirectory(labs)

include_directories(libs/boost)
include_directories(network)
include_directories(labs)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} labs network -lpthread)
