set(BUILD_SHARED_LIBS OFF)
set(BUILD_TESTING OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(proto)

message(STATUS "Subproject: Protobuf...")
# Download and unpack protobuf at configure time
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/external_protobuf.cmake
        ${CMAKE_BINARY_DIR}/protobuf-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/protobuf-download )
if(result)
    message(FATAL_ERROR "CMake step for protobuf failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/protobuf-download )
if(result)
    message(FATAL_ERROR "Build step for protobuf failed: ${result}")
endif()

set(protobuf_BUILD_TESTS OFF CACHE INTERNAL "Disable Protobuf tests")
add_subdirectory(
        ${CMAKE_BINARY_DIR}/protobuf-src/cmake
        ${CMAKE_BINARY_DIR}/protobuf-build)
message(STATUS "Subproject: Protobuf...DONE")

find_package(Protobuf REQUIRED)
# Generate Protobuf cpp sources from .proto file(s)
set(PROTO_HDRS)
set(PROTO_SRCS)
file(GLOB PROTO_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.proto)
foreach (PROTO_FILE ${PROTO_LIST})
    #message(STATUS "protoc proto: ${PROTO_FILE}")
    get_filename_component(PROTO_DIR ${PROTO_FILE} DIRECTORY)
    get_filename_component(PROTO_NAME ${PROTO_FILE} NAME_WE)
    set(PROTO_HDR ${PROJECT_BINARY_DIR}/${PROTO_DIR}/${PROTO_NAME}.pb.h)
    set(PROTO_SRC ${PROJECT_BINARY_DIR}/${PROTO_DIR}/${PROTO_NAME}.pb.cc)
    message(STATUS "protoc hdr: ${PROTO_HDR}")
    message(STATUS "protoc src: ${PROTO_SRC}")
    add_custom_command(
            OUTPUT ${PROTO_SRC} ${PROTO_HDR}
            COMMAND protobuf::protoc
            "--proto_path=${PROJECT_SOURCE_DIR}"
            "--cpp_out=${PROJECT_BINARY_DIR}"
            ${PROTO_FILE}
            DEPENDS ${PROTO_FILE} protobuf::protoc
            COMMENT "Running C++ protocol buffer compiler on ${PROTO_FILE}"
            VERBATIM)
    list(APPEND PROTO_HDRS ${PROTO_HDR})
    list(APPEND PROTO_SRCS ${PROTO_SRC})
endforeach()
#protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_LIST})


add_library(${PROJECT_NAME} ${PROTO_HDR} ${PROTO_SRC})
add_dependencies(${PROJECT_NAME} protobuf-external)


