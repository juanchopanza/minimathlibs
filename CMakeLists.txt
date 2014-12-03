#
cmake_minimum_required(VERSION 2.8)
project(minimathlibs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wuninitialized -Wconversion -Wno-missing-field-initializers -std=c++98")

# Version
# _____________________________________________________________________________
set (MINIMATHLIBS_VERSION_MAJOR "0")
set (MINIMATHLIBS_VERSION_MINOR "0")
set (MINIMATHLIBS_VERSION_PATCH "0")
set (VERSION ${MINIMATHLIBS_VERSION_MAJOR}.${MINIMATHLIBS_VERSION_MINOR}.${MINIMATHLIBS_VERSION_PATCH})

# Dependencies
# _____________________________________________________________________________

# Defines
# _____________________________________________________________________________

include_directories(${CMAKE_SOURCE_DIR}/include)

# Files
# _____________________________________________________________________________
set(MINIMATHLIBS_INCLUDEDIR ${CMAKE_SOURCE_DIR}/include/minimath)

# Targets
# _____________________________________________________________________________

# Installation
# _____________________________________________________________________________
install(DIRECTORY ${MINIMATHLIBS_INCLUDEDIR} DESTINATION include/ )

# Tests
add_subdirectory(tests bin/tests EXCLUDE_FROM_ALL)

