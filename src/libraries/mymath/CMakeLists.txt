project(mymath)

add_library(${PROJECT_NAME}_i INTERFACE)
target_include_directories(${PROJECT_NAME}_i INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} STATIC
	stub.cpp
	MyMath.h
	BoundingBox.h
	Vec2.h
	Vec3.h
)
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_i)

set_target_properties(${target} PROPERTIES FOLDER "Libraries")
