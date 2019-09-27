project("painter")

set(SRC 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/painter.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/painter.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/painter.inl"
)

add_library(${PROJECT_NAME} STATIC ${SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC 
	"geometry_i"
	"model_i"
	"tga_i"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(${PROJECT_NAME} PRIVATE ${PCH_DIR})

set_precompiled_header(${PROJECT_NAME} "${PCH_DIR}/basic_defs.h")