cmake_minimum_required(VERSION 3.10)
project(network)

set (Boost_USE_STATIC_LIBS ON)
# Boost
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB SRC_LIST ./*.cpp)

add_library(network STATIC ${SRC_LIST})
target_link_libraries(network ${Boost_LIBRARIES})