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

Minimathlibs is a header only library, and has no external dependencies other than a C++03 compliant compiler and standard library plus an implementation of TR1. All necessary header files are in include/minimath, and should be installed under ``minimath``.

To ease installment from source, CMake files are provided with the usual targets. This is an example of an installation into a custom location:

```shell
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/opt/local
make install
```

This will install the ``minimathlibs`` header files into ``/opt/local/include/minimath``.

testing
-------

The tests require cppunit. They may be built and run either directly from a provided makefile, or usiong ``cmake``:

To build and run the default tests from the makefile: from the minimathlibs directory, run

```shell
make test
```

from the minimathlibs directory.

To build and run the default tests using cmake:

```shell
mkdir build
cd build
cmake ..
make test
```


The 3D transformation part of minimathlibs is designed to work with external 3D point classes satisfying certain minimal criteria. To run the tests with a custom point class, 

```shell
make clean # clean up previous build
CXXFLAGS=-DCUSTOM_POINT make test
```
