project("renderer")

set(SRC 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/renderer.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/renderer.h"
)

add_library(${PROJECT_NAME} STATIC ${SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC 
	"geometry_i"
	"model_i"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")