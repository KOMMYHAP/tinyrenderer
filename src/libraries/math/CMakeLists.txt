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
	INTERFACE
		utils
		${PROJECT_NAME}_i
	PRIVATE
		basiclib
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Libraries")
