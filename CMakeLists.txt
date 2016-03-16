cmake_minimum_required( VERSION 2.8 )

option( foresight_test "Build tests" ON )

set( PROJ_NAME "foresight" )
set( PROJ_EXE "fore" )

file( GLOB_RECURSE PROJ_SOURCES "src/*.cc" )
file( GLOB PROJ_MAIN "src/main.cc" )
list( REMOVE_ITEM PROJ_SOURCES ${PROJ_MAIN} )
set( PROJ_INCLUDES "${CMAKE_SOURCE_DIR}/include" )

project( ${PROJ_NAME} )

#TODO Local config
set( Boost_NO_BOOST_CMAKE TRUE )

add_subdirectory( "bayesopt" )
set( BAYESOPT_INCLUDES "bayesopt/include" "bayesopt/utils" )

if ( foresight_test )
  add_subdirectory( "lib/gtest" )
  add_subdirectory( "test" )
endif()

set( CMAKE_CXX_FLAGS "-std=c++14 -Wall -Weffc++" )
set( CMAKE_CXX_FLAGS_RELEASE "-O3" )
set( CMAKE_CXX_FLAGS_DEBUG "-gdwarf-3" )

include_directories( ${PROJ_INCLUDES} )
include_directories( SYSTEM ${BAYESOPT_INCLUDES} )
add_library( ${PROJ_NAME} ${PROJ_SOURCES} )
add_executable( ${PROJ_EXE} "src/main.cc" )
target_link_libraries( ${PROJ_EXE} ${PROJ_NAME} bayesopt )

