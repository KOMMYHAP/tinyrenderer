macro(my_add_test testName)
	set(options "")
    set(oneValueArgs "")
	set(multiValueArgs SOURCES DEPENDENCIES)
	cmake_parse_arguments(MY_ADD_TEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGV})

	if (NOT MY_ADD_TEST_SOURCES)
		message(FATAL_ERROR "my_add_test requires SOURCES <source files>.")
	endif()
	list(LENGTH MY_ADD_TEST_SOURCES MY_ADD_TEST_SOURCES_LENGTH)
	if (${MY_ADD_TEST_SOURCES_LENGTH} EQUAL 0)
		message(FATAL_ERROR "my_add_test requires at least one source file in SOURCES.")
	endif()

	add_executable(${testName} ${MY_ADD_TEST_SOURCES})

	if (MY_ADD_TEST_DEPENDENCIES)
		target_link_libraries(${testName} PRIVATE ${MY_ADD_TEST_DEPENDENCIES})
	endif()

	message(STATUS "Adding test ${testName}")
	add_test(NAME ${testName} COMMAND ${testName})
endmacro()
