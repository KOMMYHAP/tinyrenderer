project(utils)

add_library(${PROJECT_NAME} STATIC
	Utils.h
	Utils.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE basiclib)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Libraries")
