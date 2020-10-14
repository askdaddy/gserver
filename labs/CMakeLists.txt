cmake_minimum_required(VERSION 3.10)
project(labs)

get_directory_property(PROTOCOL_HEADERS
        DIRECTORY ${CMAKE_SOURCE_DIR}/protocol
        DEFINITION PROTOCOL_HEADERS)
message(${PROTOCOL_HEADERS})

file(GLOB SRC_LIST ./*.cpp)
add_library(${PROJECT_NAME} STATIC ${SRC_LIST})


include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROTOCOL_HEADERS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} proto)