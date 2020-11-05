cmake_minimum_required(VERSION 3.10)
project(labs)

# Boost
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
# Protobuf
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
# Protocols
get_directory_property(PROTO_INCLUDE
        DIRECTORY ${CMAKE_SOURCE_DIR}/protocol
        DEFINITION PROTO_INCLUDE)
include_directories(${PROTO_INCLUDE})


file(GLOB SRC_LIST ./*.cpp)
add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} proto)