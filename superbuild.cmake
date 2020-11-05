include( ExternalProject )
# Compute -G arg for configuring external projects with the same CMake
# generator:
if(CMAKE_EXTRA_GENERATOR)
    set(gen "${CMAKE_EXTRA_GENERATOR} - ${CMAKE_GENERATOR}")
else()
    set(gen "${CMAKE_GENERATOR}" )
endif()

option( BUILD_BOOST_WITH_LOG "Build Boost 1.74 along with Boost.Log" ON )
if( ${BUILD_BOOST_WITH_LOG} )
    include( ${CMAKE_CURRENT_SOURCE_DIR}/external_boost.cmake )
endif()