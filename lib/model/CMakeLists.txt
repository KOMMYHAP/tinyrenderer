project("model")

set(SRC 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/model.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/model.h"
)

add_library(${PROJECT_NAME}_i INTERFACE)
add_library(${PROJECT_NAME} STATIC ${SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC 
	"${PROJECT_NAME}_i"
	"geometry_i"
)

target_include_directories(${PROJECT_NAME}_i INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")