cmake_minimum_required(VERSION 3.10)
project(labs)

file(GLOB SRC_LIST ./*.cpp)
add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})