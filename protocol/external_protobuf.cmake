cmake_minimum_required(VERSION 3.10)
# Get and build google's protobuf
# simplify variable expansion
cmake_policy(SET CMP0053 NEW)
cmake_policy(SET CMP0010 NEW)

project(protobuf-download NONE)

include(ExternalProject)
ExternalProject_Add(protobuf-external
        GIT_REPOSITORY "https://github.com/google/protobuf"
        GIT_TAG "v3.6.1"
        SOURCE_DIR "${CMAKE_BINARY_DIR}/protobuf-src"
        BINARY_DIR "${CMAKE_BINARY_DIR}/protobuf-build"
        UPDATE_COMMAND ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
        LOG_DOWNLOAD ON
)


#ExternalProject_Get_Property(protobuf-external source_dir)
#include_directories(${source_dir}/src)
#link_directories(${CMAKE_CURRENT_BINARY_DIR}/protobuf)

#set(PROTOBUF_INCLUDE_DIR ${source_dir}/src)
#set(PROTOBUF_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/protobuf)

#include_directories(${PROTOBUF_INCLUDE_DIR})
#link_directories(${PROTOBUF_LIBRARIES})