include( FindProtobuf )
message("include Protobuf")
message(${CMAKE_CURRENT_BINARY_DIR})

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
#include_directories(${CMAKE_CURRENT_BINARY_DIR})
set(PROTO_BIN_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(PROTOCOL_HEADERS ${CMAKE_CURRENT_BINARY_DIR} ${Protobuf_INCLUDE_DIRS})

file(GLOB PROTO_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.proto)
protobuf_generate_cpp(PROTO_SRC PROTO_HEADER ${PROTO_LIST})

add_library(proto ${PROTO_HEADER} ${PROTO_SRC})
target_link_libraries(proto ${PROTOBUF_LIBRARY})

