cmake_minimum_required(VERSION 3.10)
project(labs)
find_package (Threads REQUIRED)
# Boost
set (Boost_USE_STATIC_LIBS ON)
set (Boost_NO_SYSTEM_PATHS ON)
find_package(Boost 1.67.0 REQUIRED COMPONENTS date_time system)
include_directories(${Boost_INCLUDE_DIRS})

# Protobuf
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})

# Protocols
get_directory_property(PROTO_INCLUDE
        DIRECTORY ${CMAKE_SOURCE_DIR}/protocol
        DEFINITION PROTO_INCLUDE)
include_directories(${PROTO_INCLUDE})

add_executable(labs_serv server.cpp )
target_link_libraries(labs_serv ${Boost_LIBRARIES} proto ${Protobuf_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})


add_executable(labs_client client.cpp)
target_link_libraries(labs_client ${Boost_LIBRARIES} proto ${Protobuf_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})