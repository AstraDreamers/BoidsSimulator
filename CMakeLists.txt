#    BoidsSimulator - A simple flocking simulation.
#    Copyright (C) 2026  AstraDreamers
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 4.0)

project(BoidsSimulator LANGUAGES CXX VERSION 1.0)

# -----------------
# Set C++26 Feature
# -----------------

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# ----------------------------------
# Static & Dynamic Linking Configure
# ----------------------------------

if(WIN32)
	set(BUILD_SHARED_LIBS		OFF	CACHE BOOL "" FORCE)
	set(SFML_STATIC_LIBRARIES	ON	CACHE BOOL "" FORCE)
else()
	set(BUILD_SHARED_LIBS		ON	CACHE BOOL "" FORCE)
	set(SFML_STATIC_LIBRARIES	OFF	CACHE BOOL "" FORCE)
endif()


# --------------------
# Other Configurations
# --------------------

set(MBEDTLS_THREADING_C ON CACHE BOOL "" FORCE)
set(MBEDTLS_THREADING_PTHREAD ON CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)

# ---------------------------
# External Projects Importing
# ---------------------------

include(FetchContent)

FetchContent_Declare(
	sfml
	GIT_REPOSITORY 	https://github.com/SFML/SFML.git
	GIT_TAG 		3.1.0
	GIT_SHALLOW 	ON
)

FetchContent_MakeAvailable(sfml)


# -------------------
# Source Files Adding
# -------------------

add_executable(${PROJECT_NAME} 
	src/core/core.c++
	src/manager/ui/slider.c++
	src/manager/manager_entity.c++
	src/manager/manager_ui.c++
	src/main.c++
)

target_include_directories(${PROJECT_NAME} PRIVATE
	include/
)

target_precompile_headers(${PROJECT_NAME} PRIVATE
	include/pch.h++
)


# -------------------------
# Compile & Linking Options
# -------------------------

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
        /permissive-
        $<$<CONFIG:Debug>:/Zi>
        $<$<CONFIG:Release>:/O2>
        $<$<CONFIG:Release>:/fp:fast>
    )

    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:/DEBUG>
        $<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>
    )
else()
	target_compile_options(${PROJECT_NAME} PRIVATE
		$<$<CONFIG:Debug>:-g>
		$<$<CONFIG:Release>:-O3>
		$<$<CONFIG:Release>:-ffast-math>
		-Wall
		-Wextra
		-m64
	)

	target_link_options(${PROJECT_NAME} PRIVATE
		$<$<CONFIG:Release>:-mwindows>
		-static-libgcc
		-static-libstdc++
		-m64
	)

	if(WIN32)
		target_link_options(${PROJECT_NAME} PRIVATE
			-static
		)
	endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
	SFML::Graphics
	SFML::Audio
	SFML::Window
	SFML::System
)
