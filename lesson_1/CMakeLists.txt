project(lesson_1)

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB SOURCES
    "${SRC_DIR}/*.h"
    "${SRC_DIR}/*.cpp"
)

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${LIB_DIR}")

#target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
#target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
#target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

#target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
#target_link_libraries(${PROJECT_NAME} "glad")
#target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

target_include_directories(${PROJECT_NAME} PRIVATE "${TGA_DIR}/include")
target_link_libraries(${PROJECT_NAME} "tga")