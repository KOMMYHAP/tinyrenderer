project(tgaimage)

add_library(${PROJECT_NAME} STATIC
	TgaImage.h
	TgaImage.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Libraries")
