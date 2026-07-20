cmake_minimum_required(VERSION 4.0)

project(
	BoidsSimulator
	LANGUAGES CXX
	VERSION 1.0
)

set(CMAKE_CXX_STANDARD			26)
set(CMAKE_CXX_STANDARD_REQUIRED	ON)
set(CMAKE_COLOR_DIAGNOSTICS 	ON)

if(WIN32)
	set(BUILD_SHARED_LIBS		OFF	CACHE BOOL "" FORCE)
	set(SFML_STATIC_LIBRARIES	ON	CACHE BOOL "" FORCE)
else()
	set(BUILD_SHARED_LIBS		ON	CACHE BOOL "" FORCE)
	set(SFML_STATIC_LIBRARIES	OFF	CACHE BOOL "" FORCE)
endif()

include(FetchContent)

FetchContent_Declare(
	sfml
	GIT_REPOSITORY 	https://github.com/SFML/SFML.git
	GIT_TAG 		3.1.0
	GIT_SHALLOW 	ON
)

FetchContent_MakeAvailable(sfml)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
	"src/*.cpp"
	"src/*.hpp"
	"src/*.c++"
	"src/*.h++"
	"src/*.c"
	"src/*.h"
)

list(REMOVE_ITEM PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h++")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
	src/pch.h++
)

target_compile_options(${PROJECT_NAME} PRIVATE
	$<$<CONFIG:Debug>:-g>
	$<$<CONFIG:Release>:-O3>
	$<$<CONFIG:Release>:-ffast-math>
	-Wall
	-Wextra
	-m64
	-fdiagnostics-color=always
)

if(WIN32)
target_link_options(${PROJECT_NAME} PRIVATE
	$<$<CONFIG:Release>:-mwindows>
	-m64
	-static-libgcc
	-static-libstdc++
	-static
)
else()
target_link_options(${PROJECT_NAME} PRIVATE
	-m64
	-static-libgcc
	-static-libstdc++
)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
	SFML::Graphics
	SFML::Audio
	SFML::Window
	SFML::System
)

add_custom_target(update_assets ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_CURRENT_SOURCE_DIR}/assets"
	"${CMAKE_BINARY_DIR}/assets"
	COMMENT "Syncing assets to build directory..."
)

add_dependencies(${PROJECT_NAME} update_assets)
