CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

if(DEFINED PROJECT_NAME)
  set(subproject ON)
else()
  set(subproject OFF)
endif()

PROJECT(tray C CXX)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

IF(WIN32)
	SET(CMAKE_CXX_FLAGS_RELEASE "/MT")
	SET(CMAKE_CXX_FLAGS_DEBUG "/MTd")
ENDIF()

add_library(tray_base INTERFACE)

target_compile_features(tray_base INTERFACE c_std_99)

file(GLOB src
        ${CMAKE_CURRENT_LIST_DIR}/*.h
        ${CMAKE_CURRENT_LIST_DIR}/*.ico
        ${CMAKE_CURRENT_LIST_DIR}/*.png)

if(WIN32)
	include(WinApiLevels)
	add_compile_definitions(TRAY_WINAPI=1)
	list(APPEND src ${CMAKE_CURRENT_SOURCE_DIR}/tray_windows.c)
else()
	if(UNIX)
		if(APPLE)
			add_compile_definitions(TRAY_APPKIT=1)
			find_library(COCOA Cocoa REQUIRED)
			list(APPEND src ${CMAKE_CURRENT_SOURCE_DIR}/tray_darwin.m)
		else()
			FIND_PACKAGE(PkgConfig)
			PKG_CHECK_MODULES(APPINDICATOR REQUIRED appindicator3-0.1)
			ADD_DEFINITIONS(${APPINDICATOR_CFLAGS})
    	LINK_DIRECTORIES(${APPINDICATOR_LIBRARY_DIRS})
			add_compile_definitions(TRAY_APPINDICATOR=1)
			list(APPEND src ${CMAKE_CURRENT_SOURCE_DIR}/tray_linux.c)
		endif()
	endif()
endif()

add_library(tray STATIC ${src})
target_link_libraries(tray INTERFACE tray_base)

add_library(tray::tray ALIAS tray)

add_executable(tray_example ${CMAKE_CURRENT_SOURCE_DIR}/example.c)
target_link_libraries(tray_example tray::tray)

configure_file(${CMAKE_CURRENT_LIST_DIR}/icon.ico ${CMAKE_BINARY_DIR}/icon.ico COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/icon.png ${CMAKE_BINARY_DIR}/icon.png COPYONLY)

if(UNIX)
	if(APPLE)
		target_link_libraries(tray_example ${COCOA})
	else()
		target_link_libraries(tray_example ${APPINDICATOR_LIBRARIES})
	endif()
endif()

IF(NOT WIN32)
	INSTALL(FILES tray.h DESTINATION include)
ENDIF()
