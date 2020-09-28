cmake_minimum_required(VERSION 3.10)
project(network)

include_directories(${Boost_INCLUDE_DIRS})

file(GLOB SRC_LIST ./*.cpp)

add_library(${PROJECT_NAME} STATIC ${SRC_LIST} stream_buffer.cpp stream_buffer.h)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})