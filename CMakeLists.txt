cmake_minimum_required(VERSION 3.14)

# configuring compiler' and linker' flags:
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
# ----------------------------------------


# configuring cmake function-helpers:
set(CMAKE_HELPERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
add_subdirectory("${CMAKE_HELPERS_DIR}")
include("${CMAKE_HELPERS_DIR}/cotire.cmake")
# ----------------------------------


# configuring sources:
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sources")
set(LIB_DIR "${SOURCES_DIR}/lib")
set(LESSONS_DIR "${SOURCES_DIR}/lessons")
set(PCH_DIR "${SOURCES_DIR}/precompiled_headers")

add_subdirectory("${LIB_DIR}")
add_subdirectory("${LESSONS_DIR}")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT lesson_1)
# ------------------