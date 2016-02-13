cmake_minimum_required (VERSION 2.6)
project (TinyWindow)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
 
include (GNUInstallDirs)
include (CMakePackageConfigHelpers)

enable_testing()

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

if (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR 
	("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") OR (
	("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel") AND UNIX))
	option (TINYWINDOW_TEST_ENABLE_CXX11 "Enable C++ 11" off)
	option (TINYWINDOW_TEST_ENABLE_CXX1Y "Enable C++ 1y" off)
	option (TINYWINDOW_TEST_ENABLE_CXX14 "Enable C++ 14" off)
	option (TINYWINDOW_TEST_ENABLE_CXX1Z "Enable C++ 1z" off)
	set (CXX_LIBRARY "libstdc++")

	if (TINYWINDOW_TEST_ENABLE_CXX1Z)
		set (CMAKE_XCODE_CLANG_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++1z")
		set (CMAKE_XCODE_CLANG_ATTRIBUTE_CLANG_CXX_LIBRARY ${CXX_LIBRARY})
		set (CMAKE_CXX_FLAGS "-std=c++1z")
	elseif (TINYWINDOW_TEST_ENABLE_CXX14)
		set (CMAKE_XCODE_CLANG_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++14")
		set (CMAKE_XCODE_CLANG_ATTRIBUTE_CLANG_CXX_LIBRARY ${CXX_LIBRARY})
		set (CMAKE_CXX_FLAGS "-std=c++14")
	elseif (TINYWINDOW_TEST_ENABLE_CXX1Y)
		set (CMAKE_XCODE_CLANG_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++1y")
		set (CMAKE_XCODE_CLANG_ATTRIBUTE_CLANG_CXX_LIBRARY ${CXX_LIBRARY})
		set (CMAKE_CXX_FLAGS "-std=c++1y")
	elseif (TINYWINDOW_TEST_ENABLE_CXX11)
		set (CMAKE_XCODE_CLANG_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
		set (CMAKE_XCODE_CLANG_ATTRIBUTE_CLANG_CXX_LIBRARY ${CXX_LIBRARY})
		set (CMAKE_CXX_FLAGS "-std=c++11")
	endif()
endif()

option (TINYWINDOW_TEST_ENABLE_MS_EXTENSIONS "Enable MS extensions" off)

if (TINYWINDOW_TEST_ENABLE_MS_EXTENSIONS)
	if (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR
		("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
		add_definitions(-Wgnu-anonymous-struct)
		add_definitions(-Wnested-anon-types)
	endif()
else()
	if (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC") OR
		(("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel") AND WIN32))
		add_definitions(/za)
	elseif(("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR
		("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
		add_definitions(-pedantic)
	endif()
endif()

find_package(OpenGL)

if(UNIX)
set (LINK_DIRECTORY "/usr/lib/")
set (LIBS "-lX11 ${OPENGL_LIBRARIES}")
set (RELEASE_FLAGS "-std=c++11 -DSO -w -fpermissive")
set (DEBUG_FLAGS "-std=c++11 -DSO -w -g -fpermissive -DDEBUG")
endif(UNIX)

if (WIN32)
	set (LIBS "${OPENGL_LIBRARIES}")
endif(WIN32)

set (VERSION_MAJOR 0)
set (VERSION_MINOR 3)

set (INCLUDE_DIR "./include/")
set (SOURCE_DIR "./source/")
set (DEBUG_OUTPUT_DIR "./bin/Debug/")
set (RELEASE_OUTPUT_DIR "./bin/Release/")

if (CMAKE_BUILD_TYPE MATCHES Release)
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RELEASE_OUTPUT_DIR})
		add_definitions(${RELEASE_FLAGS})
elseif (CMAKE_BUILD_TYPE MATCHES Debug)
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DEBUG_OUTPUT_DIR})
		add_definitions(${DEBUG_FLAGS})
elseif(CMAKE_BUILD_TYPE MATCHES Empty)
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DEBUG_OUTPUT_DIR})
	add_definitions(${DEBUG_FLAGS})
endif()

#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set (CMAKE_CXX_FLAGS_DEBUG "${DEBUG_FLAGS}")
set (CMAKE_CXX_FLAGS_RELEASE "${RELEASE_FLAGS}")

include_directories ("${INCLUDE_DIR}")
include_directories ("${PROJECT_BINARY_DIR}")
link_directories (${LINK_DIRECTORY})
link_libraries (${LIBS})
add_executable(TinyWindow ./source/Example.cpp)
