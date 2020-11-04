find_package(Boost)

include( ExternalProject )

message( "External project - Boost" )

set( Boost_Bootstrap_Command )
if( UNIX )
    set( Boost_Bootstrap_Command ./bootstrap.sh )
    set( Boost_b2_Command ./b2 )
else()
    if( WIN32 )
        set( Boost_Bootstrap_Command bootstrap.bat )
        set( Boost_b2_Command b2.exe )
    endif()
endif()

ExternalProject_Add(Boost
        GIT_REPOSITORY "https://github.com/boostorg/boost.git"
        GIT_TAG boost-1.74.0
        PREFIX boost-1_74
        BUILD_IN_SOURCE 1
        UPDATE_COMMAND ""
        PATCH_COMMAND ""
        CONFIGURE_COMMAND ${Boost_Bootstrap_Command}
        --prefix=${CMAKE_BINARY_DIR}/INSTALL
        BUILD_COMMAND  ${Boost_b2_Command} install
        --without-python
        --without-mpi
        --disable-icu
        --prefix=${CMAKE_BINARY_DIR}/INSTALL
        --threading=single,multi
        --link=static
        --variant=releas
        -j8
        INSTALL_COMMAND ""
        INSTALL_DIR ${CMAKE_BINARY_DIR}/INSTALL
        )

if(NOT ${Boost_FOUND})
    #rerun cmake in initial build
    #will update cmakecache/project files on first build
    #so you may have to reload project after first build
    add_custom_target(Rescan ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} DEPENDS Boost)
else()
    #Rescan becomes a dummy target after first build
    #this prevents cmake from rebuilding cache/projects on subsequent builds
    add_custom_target(Rescan)
endif()



if( NOT WIN32 )
    set(Boost_LIBRARY_DIR ${CMAKE_BINARY_DIR}/INSTALL/lib/boost/ )
    set(Boost_INCLUDE_DIR ${CMAKE_BINARY_DIR}/INSTALL/include/ )
else()
    set(Boost_LIBRARY_DIR ${CMAKE_BINARY_DIR}/INSTALL/lib/ )
    set(Boost_INCLUDE_DIR ${CMAKE_BINARY_DIR}/INSTALL/include/boost-1_74/ )
endif()