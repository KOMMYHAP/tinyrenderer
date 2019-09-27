# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
set_target_properties("glfw" PROPERTIES FOLDER "Libraries")

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_subdirectory("${GLAD_DIR}")
set_target_properties("glad" PROPERTIES FOLDER "Libraries")

# TGA
set(TGA_DIR "${LIB_DIR}/tga")
add_subdirectory("${TGA_DIR}")
set_target_properties("tga" PROPERTIES FOLDER "Libraries")

# obj model
set(MODEL_DIR "${LIB_DIR}/model")
add_subdirectory("${MODEL_DIR}")
set_target_properties("model" PROPERTIES FOLDER "Libraries")

# geometry
set(GEOMETRY_DIR "${LIB_DIR}/geometry")
add_subdirectory("${GEOMETRY_DIR}")
set_target_properties("geometry" PROPERTIES FOLDER "Libraries")

# renderer
set(RENDERER_DIR "${LIB_DIR}/renderer")
add_subdirectory("${RENDERER_DIR}")
set_target_properties("renderer" PROPERTIES FOLDER "Libraries")
