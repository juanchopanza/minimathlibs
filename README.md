minimathlibs
============

A collection of small mathematical tools for everyday problem solving.

Two main aspects: 

* 3D geometry: points and transformations.
* small, statically sized matrices.

Based on concepts used in code developed during my time at CERN.

Author: Juan Palacios https://github.com/juanchopanza

License: 2-clause BSD license.

building
--------

Minimathlibs is a header only library, and has no external dependencies other than a C++03 compliant compiler and standard library plus an implementation of TR1. All necessary header files are in include/Math, and should be installed under ``Math``.

testing
-------

The tests require cppunit.

From the minimathlibs directory, run

```shell
make test
```

to build and run the default tests.

The 3D transformation part of minimathlibs is designed to work with external 3D point classes satisfying certain minimal criteria. To run the tests with a custom point class, 

```shell
make clean # clean up previous build
CXXFLAGS=-DCUSTOM_POINT make test
```
