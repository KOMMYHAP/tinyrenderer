# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
set(GLFW_DIR "${GLFW_DIR}" PARENT_SCOPE)
add_subdirectory("${GLFW_DIR}")

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
set(GLAD_DIR "${GLAD_DIR}" PARENT_SCOPE)
add_subdirectory("${GLAD_DIR}")

# TGA
set(TGA_DIR "${LIB_DIR}/tga")
set(TGA_DIR "${TGA_DIR}" PARENT_SCOPE)
add_subdirectory("${TGA_DIR}")