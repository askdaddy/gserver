cmake_minimum_required(VERSION 3.10)
project(gserver)
set(CMAKE_CXX_STANDARD 11)


include(${CMAKE_SOURCE_DIR}/superbuild.cmake)


#add_subdirectory(protocol)
#add_subdirectory(network)
#add_subdirectory(labs)

#include_directories(network)
#include_directories(labs)

add_executable(${PROJECT_NAME} main.cpp reflection/factory.h reflection/classes.h)

target_link_libraries(${PROJECT_NAME} -lpthread)
