include(cmake_helpers/my_add_test.cmake)

my_add_test(Stub SOURCES Stub.cpp)
my_add_test(BoundingBox SOURCES BoundingBox.cpp DEPENDENCIES mymath)
