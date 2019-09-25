cmake_minimum_required(VERSION 3.14)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++17" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++17")
    endif()
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W4 -Zi")
set(CMAKE_CONFIGURATION_TYPES Debug RelWithDebInfo CACHE STRING INTERNAL FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
add_subdirectory("${LIB_DIR}")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lesson_1")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lesson_2")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lesson_3")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT lesson_1)