project(proto)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})

# Generate Protobuf cpp sources from .proto file(s)
file(GLOB PROTO_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.proto)
protobuf_generate_cpp(PROTO_SRC PROTO_HDR ${PROTO_LIST})

add_library(${PROJECT_NAME} ${PROTO_HDR} ${PROTO_SRC})

set(PROTO_INCLUDE ${CMAKE_CURRENT_BINARY_DIR})