project(graphics)

add_library(${PROJECT_NAME} STATIC
	Canvas.cpp
	Canvas.h
	Texture.h
	Texture.cpp
	Color.h
	Model.cpp
	Model.h
	PixelsRow.h
	PixelsRow.cpp
	TextureView.h
	TextureView.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}
	PUBLIC
		math
		tgaimage
	PRIVATE
		basiclib
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Libraries")
