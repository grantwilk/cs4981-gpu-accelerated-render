# cmake configuration
set( CMAKE_SYSTEM_NAME Linux )
cmake_minimum_required( VERSION 3.10.2 )

# project configuration
project( cs4981-gpu-accelerated-render CUDA )
set( CMAKE_CUDA_STANDARD 14 )

# directory variables
set( PROJECT_DIR ${CMAKE_HOME_DIRECTORY} )
set( SOURCE_DIR  ${PROJECT_DIR}/src )

# include files
include_directories(
    ${SOURCE_DIR}
    ${SOURCE_DIR}/graphics
    ${SOURCE_DIR}/graphics/context
    ${SOURCE_DIR}/graphics/shapes
    ${SOURCE_DIR}/io
    ${SOURCE_DIR}/matrix
)
file( GLOB_RECURSE SOURCES
        ${SOURCE_DIR}/*.c
        ${SOURCE_DIR}/*.cu
)

# add executable
add_executable( ${PROJECT_NAME} ${SOURCES} )

# find and include x11 library
# find_package( X11 REQUIRED )

set( X11_FOUND 1 )
set( X11_INCLUDE_DIR /usr/include/X11 )
set( X11_LIBRARIES /usr/lib/x86_64-linux-gnu/libX11.so )

message( STATUS "X11_FOUND = ${X11_FOUND}" )
message( STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}" )
message( STATUS "X11_LIBRARIES = ${X11_LIBRARIES}" )

include_directories( ${X11_INCLUDE_DIR} )
link_directories( ${X11_LIBRARIES} )
target_link_libraries( ${PROJECT_NAME} ${X11_LIBRARIES} )
