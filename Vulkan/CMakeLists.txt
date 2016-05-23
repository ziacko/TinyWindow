cmake_minimum_required (VERSION 2.6)
project (TinyWindow_Vulkan CXX)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
 
include (GNUInstallDirs)
include (CMakePackageConfigHelpers)

set(PROJECT_LABEL "Vulkan")

#enable_testing()

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

find_package(OpenGL)
link_directories("./lib")
target_link_libraries(${TARGET} vulkan-1)

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
	#find_library(VULKAN_LIB NAMES vulkan-1 vulkan PATHS ${CMAKE_SOURCE_DIR}/lib)
	#target_link_libraries(${TARGET} ${VULKAN_LIB})
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	
else(WIN32)
	find_library(VULKAN_LIBS NAMES libvulkan.so PATHS ${CMAKE_SOURCE_DIR}/libs/vulkan)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

endif(WIN32)

set (VERSION_MAJOR 0)
set (VERSION_MINOR 4)

set (TINYWINDOW_INCLUDE_DIR "../Include")
set (EXAMPLE_INCLUDE_DIR "./Include")
set (DEBUG_OUTPUT_DIR "./bin/Debug/")
set (RELEASE_OUTPUT_DIR "./bin/Release/")
set (OUTPUT_DIR "./bin")

if ( MSVC )
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${DEBUG_OUTPUT_DIR}")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${RELEASE_OUTPUT_DIR}")	
endif( MSVC )

set (CMAKE_CXX_FLAGS_DEBUG "${DEBUG_FLAGS}")
set (CMAKE_CXX_FLAGS_RELEASE "${RELEASE_FLAGS}")



include_directories ("${TINYWINDOW_INCLUDE_DIR}")
include_directories ("${EXAMPLE_INCLUDE_DIR}")
include_directories ("${PROJECT_BINARY_DIR}")
link_directories (${LINK_DIRECTORY})
link_libraries (${LIBS})
SET ( SOURCE Vulkan.cpp)
SET ( HEADER_FILES ${TINYWINDOW_INCLUDE_DIR}/TinyWindow.h)

add_executable(TinyWindow_Vulkan ${SOURCE} ${HEADER_FILES})
set_property(TARGET TinyWindow_Vulkan PROPERTY OUTPUT_NAME "Example")
