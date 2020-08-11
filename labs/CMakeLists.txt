cmake_minimum_required(VERSION 3.10)
project(labs)
set(CMAKE_CXX_STANDARD 14)

include_directories(../libs/boost/)

file(GLOB SRC_LIST ./*.cpp)
file(GLOB BOOST_STATIC_LIBS ../libs/boost/stage/lib/*.lib)

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})
#add_library(sub::liblabs ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} ${BOOST_STATIC_LIBS})