project(basiclib LANGUAGES CXX)

add_library(${PROJECT_NAME}_i INTERFACE)
target_include_directories(${PROJECT_NAME}_i INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_precompile_headers(${PROJECT_NAME}_i INTERFACE
	basicdefs.h
	stdheaders.h
)
target_compile_definitions(${PROJECT_NAME}_i
	INTERFACE
		$<$<CONFIG:Release>:WUSIKO_IS_PRODUCTION=1>
)

add_library(${PROJECT_NAME} STATIC
	basicdefs.cpp
)
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_i)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Libraries")
