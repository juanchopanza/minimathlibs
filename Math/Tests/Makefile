#
# Copyright (c) 2012 Juan Palacios juan.palacios.puyana@gmail.com
# This file is part of minimathlibs.
# Subject to the 2-clause BSD license 
# - see <http://opensource.org/licenses/BSD-2-Clause>
#

include ../rules.mk
LDFLAGS += -lcppunit
TESTDIR = .
BUILDDIR = $(TESTDIR)/Build
TESTBIN = $(TESTDIR)/Build
TESTSRC = $(wildcard $(TESTDIR)/*.cpp)
TESTFIXTURES = $(wildcard $(TESTDIR)/*.h)
TESTOBJS = $(patsubst $(TESTDIR)/%.cpp, $(TESTBIN)/%.o, $(TESTSRC))
TESTS = $(patsubst $(TESTDIR)/%.cpp, $(TESTBIN)/%, $(TESTSRC))

# general rule for tests
#$(TESTBIN)/% : $(TESTDIR)/%.cpp $(INCLUDEDIR)/Math/%.h $(TESTBIN)/.f
#	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< $(LDFLAGS) -o $@

list :
	@echo $(TESTSRC)
	@echo $(TESTOBJS)
	@echo $(TESTS)

tests : tests.cpp $(TESTSFIXTURES) $(TESTBIN)/.f
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) tests.cpp $(LDFLAGS) -o $(TESTBIN)/$@

$(TESTBIN)/.f :
	@mkdir -p $(dir $@)
	@touch $@

clean :
	@rm -rf $(TESTBIN)
