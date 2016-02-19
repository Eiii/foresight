cmake_minimum_required( VERSION 2.8 )

set( TEST_NAME "foresight_test" )

file( GLOB_RECURSE TEST_SOURCES "*.cc" )

set( CMAKE_CXX_FLAGS "-static-libstdc++" )

include_directories( SYSTEM ${gtest_SOURCE_DIR}/include )
include_directories( ${PROJ_INCLUDES} )
add_executable( ${TEST_NAME} ${TEST_SOURCES} )
target_link_libraries( ${TEST_NAME} ${PROJ_NAME} gtest gtest_main pthread )
