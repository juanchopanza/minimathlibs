#
# Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
# This file is part of minimathlibs.
# Subject to the 2-clause BSD license 
# - see <http://opensource.org/licenses/BSD-2-Clause>
#

TOP := $(dir $(lastword $(MAKEFILE_LIST)))
INCLUDEDIR = $(TOP)include
CPPFLAGS += -I$(INCLUDEDIR)
CXXFLAGS += -Wall -Wextra -Wconversion -Wfloat-equal -pedantic-errors -O2 -g
#CXX = /usr/bin/g++
