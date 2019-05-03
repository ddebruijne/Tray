CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

#
# Here we check whether mio is being configured in isolation or as a component
# of a larger project. To do so, we query whether the `PROJECT_NAME` CMake
# variable has been defined. In the case it has, we can conclude mio is a
# subproject.
#
# This convention has been borrowed from the Catch C++ unit testing library.
#
if(DEFINED PROJECT_NAME)
  set(subproject ON)
else()
  set(subproject OFF)
endif()

PROJECT(tray C)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Generate 'compile_commands.json' for clang_complete
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

IF(WIN32)
	SET(CMAKE_CXX_FLAGS_RELEASE "/MT")
	SET(CMAKE_CXX_FLAGS_DEBUG "/MTd")
ENDIF()

add_library(tray_base INTERFACE)

target_compile_features(tray_base INTERFACE c_std_99)

if(WIN32)
	include(WinApiLevels)
else()
    add_library(tray INTERFACE)
	target_link_libraries(tray INTERFACE tray_base)
endif()

add_library(tray::tray ALIAS tray)

add_executable(tray_example example.c)
target_link_libraries(tray_example INTERFACE tray_base)

IF(NOT WIN32)
	INSTALL(FILES tray.h DESTINATION include)
ENDIF()
