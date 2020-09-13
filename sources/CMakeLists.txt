project(TinyRenderer)

set(SRCS
	main.cpp
	geometry.h
	model.h
	model.cpp
	tgaimage.h
	tgaimage.cpp)

add_executable(${PROJECT_NAME} ${SRCS})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRCS})

target_compile_definitions(${PROJECT_NAME} PRIVATE /W4 /std:c++17 $<$<CONFIG:Release>:/GL>)
target_link_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Release>:/LTCG:INCREMENTAL>)
target_precompile_headers(${PROJECT_NAME} PRIVATE basicdefs.h)