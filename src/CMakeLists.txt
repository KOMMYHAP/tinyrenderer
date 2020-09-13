project(tinyrenderer)

add_executable(${PROJECT_NAME}
	main.cpp
	geometry.h
	model.cpp
	model.h
	tgaimage.cpp
	tgaimage.h
	basicdefs.h
)
target_precompile_headers(${PROJECT_NAME} PRIVATE basicdefs.h)
