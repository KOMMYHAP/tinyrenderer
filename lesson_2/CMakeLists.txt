project(lesson_2)

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB SOURCES
    "${SRC_DIR}/*.h"
    "${SRC_DIR}/*.cpp"
)

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")

target_include_directories(${PROJECT_NAME} PRIVATE "${TGA_DIR}/include")
target_link_libraries(${PROJECT_NAME} "tga")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Lessons")