# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
set(GLFW_DIR "${GLFW_DIR}" PARENT_SCOPE)
add_subdirectory("${GLFW_DIR}")
set_target_properties("glfw" PROPERTIES FOLDER "Libraries")

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
set(GLAD_DIR "${GLAD_DIR}" PARENT_SCOPE)
add_subdirectory("${GLAD_DIR}")
set_target_properties("glad" PROPERTIES FOLDER "Libraries")

# TGA
set(TGA_DIR "${LIB_DIR}/tga")
set(TGA_DIR "${TGA_DIR}" PARENT_SCOPE)
add_subdirectory("${TGA_DIR}")
set_target_properties("tga" PROPERTIES FOLDER "Libraries")

# obj model
set(MODEL_DIR "${LIB_DIR}/model")
set(MODEL_DIR "${MODEL_DIR}" PARENT_SCOPE)
add_subdirectory("${MODEL_DIR}")
set_target_properties("model" PROPERTIES FOLDER "Libraries")

# geometry
set(GEOMETRY_DIR "${LIB_DIR}/geometry")
set(GEOMETRY_DIR "${GEOMETRY_DIR}" PARENT_SCOPE)
add_subdirectory("${GEOMETRY_DIR}")
set_target_properties("geometry" PROPERTIES FOLDER "Libraries")