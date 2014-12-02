# Tests
# _____________________________________________________________________________
file(GLOB TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/Test*.cpp)
add_library(minimathlibs_tests SHARED ${TEST_SRC})
add_executable(test_runner ${CMAKE_CURRENT_SOURCE_DIR}/tests.cpp)
target_link_libraries(test_runner cppunit)
target_link_libraries(test_runner minimathlibs_tests)

add_custom_target(test)
add_dependencies(test test_runner)

add_custom_command(TARGET test POST_BUILD COMMAND test_runner)
