cmake_minimum_required(VERSION 4.0)
project(BoidsSimulatior)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SFML_STATIC_LIBRARIES ON CACHE BOOL "" FORCE)

include(FetchContent)

FetchContent_Declare(
	sfml 
	GIT_REPOSITORY https://github.com/SFML/SFML.git 
	GIT_TAG 3.1.0
	GIT_SHALLOW ON
)

FetchContent_Declare(
	entt
	GIT_REPOSITORY https://github.com/skypjack/entt.git 
	GIT_TAG v3.16.0
	GIT_SHALLOW ON
)

FetchContent_MakeAvailable(sfml entt)

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
  -fdiagnostics-color=always
  $<$<CONFIG:Debug>:-g>
  -Wall
  -Wextra
  $<$<CONFIG:Release>:-Ofast>
  -m64
)

target_link_options(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Release>:-mwindows>
  -static-libgcc
  -static-libstdc++
  -static
  -m64
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  SFML::Graphics
  SFML::Audio
  SFML::Window
  SFML::System
  EnTT::EnTT
  opengl32
  freetype
  winmm
  gdi32
  ogg
  ws2_32
  vorbis
  vorbisenc
  vorbisfile
)

add_custom_target(update_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "${CMAKE_BINARY_DIR}/assets"
    COMMENT "Syncing assets to build directory..."
)

add_dependencies(${PROJECT_NAME} update_assets)