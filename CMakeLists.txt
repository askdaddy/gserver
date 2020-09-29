cmake_minimum_required(VERSION 3.10)
project(gserver)
set(CMAKE_CXX_STANDARD 11)
# boost
include(${CMAKE_CURRENT_SOURCE_DIR}/external_boost.cmake)

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
find_package(Boost 1.74.0)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost NOT found.")
endif()

include_directories(${Boost_INCLUDE_DIRS})

#add_subdirectory(network)
add_subdirectory(labs)

#include_directories(network)
include_directories(labs)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} labs -lpthread)
