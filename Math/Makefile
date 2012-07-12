#
# Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
# This file is part of minimathlibs.
# Subject to the Lesser GNU Public License 
# - see < http://www.gnu.org/licenses/lgpl.html>
#

include rules.mk
TESTDIR = Tests

.PHONY : all

all :tests

list_tests :
	make -C $(TESTDIR) list

tests :
	make -C $(TESTDIR) tests 

clean :
	make -C $(TESTDIR) clean
