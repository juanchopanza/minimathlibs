minimathlibs
============

A collection of small mathematical tools for everyday problem solving.

Two main aspects: 3D geometry and small, statically sized matrices.

Based on concepts used in code developed during my time at CERN.

Author: Juan Palacios juan.palacios.puyana@gmail.com

License: 2-clause BSD license.

building
--------

Minimathlibs is a header only library, and has no external dependencies other than a C++03 compliant compiler and standard library plus an implementation of TR1. All necessary header files are in Math/include/Math.

testing
-------

The tests require cppunit.

From the Math directory, run

make tests

to build and run the default tests.

The 3D transformation part of minimathlibs is designed to work with external 3D point classes satisfying certain minimal criteria. To run the tests with a custom point class, 

make clean # clean up previoue build
CXXFLAGS=-DCUSTOM_POINT make test

