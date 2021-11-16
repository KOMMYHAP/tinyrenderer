cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

project("Tiny Renderer" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin" CACHE INTERNAL "Project directory")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_OUTPUT_DIR}")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED OUTPUT IPO_CHECK_ERROR LANGUAGES CXX)
if (IPO_SUPPORTED)
	set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
	message(STATUS "IPO/LTE is turned on.")
else()
	message(STATUS "IPO/LTE optimization is not supported: ${IPO_CHECK_ERROR}.")
endif()

add_subdirectory(src)

if (BUILDING_TESTING)
	message(STATUS "${PROJECT_NAME} will perform tests.")
	enable_testing()
	add_subdirectory(tests)
else()
	message(STATUS "${PROJECT_NAME} will skip tests.")
endif()
