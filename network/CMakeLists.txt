cmake_minimum_required(VERSION 3.10)
project(network)

# Boost
set (Boost_USE_STATIC_LIBS ON)
set (Boost_NO_SYSTEM_PATHS ON)
find_package(Boost 1.67.0 REQUIRED COMPONENTS date_time system)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB SRC_LIST ./*.cpp)
add_library(network STATIC ${SRC_LIST})
target_link_libraries(network ${Boost_LIBRARIES})