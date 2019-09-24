set(SRC 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/tgaimage.cpp"
)

set(HEADERS 
	"${CMAKE_CURRENT_SOURCE_DIR}/include/tgaimage.h"
)

add_library("tga" ${SRC} ${HEADERS})

target_include_directories("tga" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories("tga" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")