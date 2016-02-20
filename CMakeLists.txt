cmake_minimum_required( VERSION 2.8 )

option( foresight_test "Build tests" ON )

set( PROJ_NAME "foresight" )
set( PROJ_EXE "fore" )

file( GLOB_RECURSE PROJ_SOURCES "src/*.cc" )
list( REMOVE_ITEM PROJ_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc" )
set( PROJ_INCLUDES "${CMAKE_SOURCE_DIR}/include" )

set( CMAKE_CXX_COMPILER "/usr/local/common/gcc-5.2.0/bin/g++" )
set( CMAKE_CXX_FLAGS "-std=c++14 -Wall -Weffc++" )
set( CMAKE_CXX_FLAGS_RELEASE "-O3" )

project( ${PROJ_NAME} )

include_directories( ${PROJ_INCLUDES} )
include_directories( SYSTEM ${gtest_SOURCE_DIR}/include )
add_library( ${PROJ_NAME} ${PROJ_SOURCES} )
add_executable( ${PROJ_EXE} "src/main.cc" )
target_link_libraries( ${PROJ_EXE} ${PROJ_NAME} )

if ( foresight_test )
  set( CMAKE_CXX_FLAGS "" )
  add_subdirectory( "lib/gtest" )
  add_subdirectory( "test" )
endif()
