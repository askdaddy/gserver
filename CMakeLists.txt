cmake_minimum_required(VERSION 3.10)
project(gserver)
set(CMAKE_CXX_STANDARD 11)
find_package (Threads REQUIRED)

include( ${CMAKE_CURRENT_SOURCE_DIR}/external_boost.cmake )
find_package(Boost 1.67.0 REQUIRED COMPONENTS date_time system)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(protocol)
add_subdirectory(network)
add_subdirectory(labs)
add_subdirectory(multiple)

include_directories(network)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} network ${CMAKE_THREAD_LIBS_INIT})
