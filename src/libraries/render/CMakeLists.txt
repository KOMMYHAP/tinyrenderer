project(render)

add_library(${PROJECT_NAME} STATIC
	BoundingBox.h
	Canvas.cpp
	Canvas.h
	Color.h
	geometry.cpp
	geometry.h
	Model.cpp
	Model.h
	PixelsRow.cpp
	PixelsRow.h
	Texture.cpp
	Texture.h
	Utils.cpp
	Utils.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}
	PUBLIC
		tgaimage
	PRIVATE
		basiclib
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Libraries")
