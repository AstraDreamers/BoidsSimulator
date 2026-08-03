cmake_minimum_required(VERSION 4.0)

project(BoidsSimulator LANGUAGES CXX VERSION 1.0)

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


# --------------------
# Standard C++26 Setup
# --------------------

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_26)


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


# ------------------------
# Moving assets/ To build/
# ------------------------

add_custom_target(update_assets ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets" "${CMAKE_BINARY_DIR}/assets"
	COMMENT "[External Job] Syncing assets to build directory."
)

add_dependencies(${PROJECT_NAME} update_assets)
