project(utils)

add_library(${PROJECT_NAME}_i INTERFACE)
target_include_directories(${PROJECT_NAME}_i INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} STATIC
	Utils.h
	Utils.cpp
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		${PROJECT_NAME}_i
	PRIVATE
		basiclib
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Libraries")
