include(cmake_helpers/my_add_test.cmake)

my_add_test(BoundingBox SOURCES BoundingBox.cpp DEPENDENCIES math)
my_add_test(Vector SOURCES Vector.cpp DEPENDENCIES math)
