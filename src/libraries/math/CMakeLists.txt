project(math)

add_library(${PROJECT_NAME} STATIC
	stub.cpp
	BoundingBox.h
	Matrix.h
	MathLib.h
	Vec2.h
	Vec3.h
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		utils
	PRIVATE
		basiclib
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Libraries")
