project(TinyRenderer)

add_subdirectory(libraries)

add_executable(${PROJECT_NAME}
	main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	basiclib
	graphics
	math
	tgaimage
	utils
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Application")
