set(SRC 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c"
)

set(HEADERS 
	"${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/khr/khrplatform.h"
)

add_library("glad" ${SRC} ${HEADERS})

target_include_directories("glad" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories("glad" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")