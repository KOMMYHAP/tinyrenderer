project(lesson_5)

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB SOURCES
    "${SRC_DIR}/*.h"
    "${SRC_DIR}/*.cpp"
)

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
	
target_link_libraries(${PROJECT_NAME} 
	"tga"
	"model"
	"geometry"
	"painter"
)

target_include_directories(${PROJECT_NAME} PRIVATE ${PCH_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Lessons")

set_precompiled_header(${PROJECT_NAME} "${PCH_DIR}/basic_defs.h")