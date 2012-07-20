#
# Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
# This file is part of minimathlibs.
# Subject to the 2-clause BSD license 
# - see <http://opensource.org/licenses/BSD-2-Clause>
#

include ../rules.mk
LDFLAGS += -lcppunit
HEADERS = $(wildcard $(INCLUDEDIR)/Math/*.h)
TESTDIR = .
BUILDDIR = $(TESTDIR)/Build
TESTBIN = $(TESTDIR)/Build
TESTSRC = $(wildcard $(TESTDIR)/*.cpp)
TESTOBJSRC = $(wildcard $(TESTDIR)/objs/*.cpp)
TESTFIXTURES = $(wildcard $(TESTDIR)/*.h)
TESTOBJS = $(patsubst $(TESTDIR)/objs/%.cpp, $(TESTBIN)/%.o, $(TESTOBJSRC))
TESTS = $(patsubst $(TESTDIR)/%.cpp, $(TESTBIN)/%, $(TESTSRC))

list :
	@echo $(HEADERS)
	@echo $(TESTDIR)
	@echo $(TESTSRC)
	@echo $(TESTS)
	@echo $(TESTOBJSRC)
	@echo $(TESTOBJS)
	@echo $(TESTFIXTURES)
	@echo $(PWD)

.PHONY: tests
.PHONY: obj_main
.PHONY: objs

tests : $(TESTBIN)/tests

obj_main : $(TESTBIN)/obj_main

objs : $(TESTOBJS)

$(TESTBIN)/tests : tests.cpp $(TESTFIXTURES) $(HEADERS) $(TESTBIN)/.f
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< $(LDFLAGS) -o $@

$(TESTBIN)/obj_main : obj_main.cpp $(TESTOBJS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(TESTOBJS) $< $(LDFLAGS) -o $@

$(TESTBIN)/%.o : $(TESTDIR)/objs/%.cpp $(HEADERS) $(TESTBIN)/.f
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

$(TESTBIN)/.f :
	@mkdir -p $(dir $@)
	@touch $@

clean :
	@rm -rf $(TESTBIN)
