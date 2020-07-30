cmake_minimum_required(VERSION 3.10)
project(gserver)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(network)

include_directories(libs/boost)
include_directories(network)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${CMAKE_BINARY_DIR}/network sub::libnetwork -lpthread)