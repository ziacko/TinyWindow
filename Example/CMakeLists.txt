cmake_minimum_required (VERSION 2.6)
project (TinyWindow_Example CXX)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

find_package(OpenGL)

if(UNIX)
set (LINK_DIRECTORY "/usr/lib/")
set (LIBS "-lX11 ${OPENGL_LIBRARIES}")
set (RELEASE_FLAGS "-std=c++11 -DSO -Wall -Wextra 2> errors.txt")
set (DEBUG_FLAGS "-std=c++11 -DSO -Wall -Wextra -g -DDEBUG 2> errors.txt")

if (CMAKE_BUILD_TYPE MATCHES Release)
	add_definitions(${RELEASE_FLAGS})
elseif (CMAKE_BUILD_TYPE MATCHES Debug)
	add_definitions(${DEBUG_FLAGS})
elseif (CMAKE_BUILD_TYPE MATCHES "")
	add_definitions(${DEBUG_FLAGS})
endif()

endif(UNIX)

if (WIN32)
	set (LIBS "${OPENGL_LIBRARIES}")
endif(WIN32)

set (VERSION_MAJOR 0)
set (VERSION_MINOR 4)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG ${DEBUG_FLAGS}")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG ${RELEASE_FLAGS}")

include_directories (../Include/)
add_executable(
	TinyWindow_Example
		Example.cpp
		Extra.cpp
		../Include/TenyWindow.hpp)
