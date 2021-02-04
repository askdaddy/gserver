cmake_minimum_required(VERSION 3.10)
project(gserver)
set(CMAKE_CXX_STANDARD 11)
find_package (Threads REQUIRED)

include(${CMAKE_SOURCE_DIR}/superbuild.cmake)

set (Boost_USE_STATIC_LIBS ON)
set (Boost_NO_SYSTEM_PATHS ON)
find_package(Boost 1.67.0 REQUIRED COMPONENTS date_time system)
message("boost libs ${Boost_LIBRARIES}")
add_subdirectory(network)

include_directories(network)
include_directories(${Boost_INCLUDE_DIR})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}  network  ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
