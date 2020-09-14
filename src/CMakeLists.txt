project(TinyRenderer)

add_subdirectory(libraries)

add_executable(${PROJECT_NAME}
	main.cpp
	model.cpp
	model.h
	tgaimage.cpp
	tgaimage.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	mymath
)

target_precompile_headers(${PROJECT_NAME} PRIVATE basicdefs.h)
set_target_properties(${target} PROPERTIES FOLDER "TinyRenderer")
