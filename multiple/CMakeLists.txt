cmake_minimum_required(VERSION 3.10)
project(multiple)
find_package (Threads REQUIRED)

message("Cmake multiple - ${PROJECT_NAME}")

file(GLOB SRC_LIST ./*.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})