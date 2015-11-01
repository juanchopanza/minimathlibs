# Tests
# _____________________________________________________________________________
# OSX needs MACOSX_RPATH
if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
    set(CMAKE_SKIP_BUILD_RPATH FALSE)
endif()

find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
add_definitions(-DBOOST_ALL_DYN_LINK)


# Unit Tests
# _____________________________________________________________________________

file(GLOB TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/Test*.cpp)

foreach(CURRENT ${TEST_SRC})
    string(REGEX REPLACE ".*/(.*)\\.cpp" "\\1" TEST_NAME ${CURRENT})
    add_executable(${TEST_NAME} ${CURRENT})
    target_link_libraries(${TEST_NAME} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
    add_test(NAME ${TEST_NAME} COMMAND $<TARGET_FILE:${TEST_NAME}>)
    set_tests_properties(${TEST_NAME} PROPERTIES LABELS "unit;all")
endforeach(CURRENT)
