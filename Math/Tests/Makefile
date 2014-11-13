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
BUILDDIR = $(TESTDIR)/.build
TESTBIN = $(TESTDIR)/.build
TESTSRC = $(wildcard $(TESTDIR)/*.cpp)
TESTDUMMYOBJSRC = $(wildcard $(TESTDIR)/objs/*.cpp)
TESTFIXTURES = $(wildcard $(TESTDIR)/*.h)
TESTDUMMYOBJS = $(patsubst $(TESTDIR)/objs/%.cpp, $(TESTBIN)/%.o, $(TESTDUMMYOBJSRC))
TESTOBJS = $(patsubst $(TESTDIR)/%.cpp, $(TESTBIN)/%.o, $(TESTSRC))
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

.PHONY: test
.PHONY: build_tests
.PHONY: obj_main
.PHONY: objs


test: build_tests
	$(TESTBIN)/tests

build_tests : $(TESTBIN)/tests

obj_main : $(TESTBIN)/obj_main

dummy_objs : $(TESTDUMMYOBJS)

objs : $(TESTOBJS)

$(TESTBIN)/tests : objs
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(TESTOBJS) $(LDFLAGS) -o $@

$(TESTBIN)/obj_main : obj_main.cpp $(TESTOBJS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(TESTOBJS) $< $(LDFLAGS) -o $@

#$(TESTBIN)/%.o : $(TESTDIR)/objs/%.cpp $(HEADERS) $(TESTBIN)/.f
#	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

$(TESTBIN)/%.o : $(TESTDIR)/%.cpp $(HEADERS) $(TESTFIXTURES) $(TESTBIN)/.f
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@


$(TESTBIN)/.f :
	@mkdir -p $(dir $@)
	@touch $@

clean :
	@rm -rf $(TESTBIN)
