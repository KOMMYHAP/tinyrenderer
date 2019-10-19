project(glad)

set(HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/glad/gl.h")
set(SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/empty.cpp")

add_library(${PROJECT_NAME} ${SRCS} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
