cmake_minimum_required(VERSION 2.6)
		
#Configuration du projet
project(worms)
set(EXECUTABLE_OUTPUT_PATH ../build/${CMAKE_BUILD_TYPE})
include_directories(include)



#Configuration de l'exécutable
file(
	GLOB_RECURSE
	source_files
	src/*
)
add_executable(
	worms
	${source_files}
)

target_link_libraries(
	worms
	sfml-system
	sfml-window
	sfml-graphics
)
