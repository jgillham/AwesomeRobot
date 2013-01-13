include settings.mk
include ../../AVR-makefile

TESTDIR=test
TESTBINDIR=$(TESTDIR)/bin
TESTRESULTSDIR=$(TESTDIR)/results

TESTSRC=$(wildcard $(TESTDIR)/*.cpp)
TESTRESULTS=$(TESTSRC:$(TESTDIR)/%.cpp=$(TESTRESULTSDIR)/%.out)
TestAll: Dirs $(TESTRESULTS)

Dirs:
	mkdir -p $(TESTBINDIR)
	mkdir -p $(TESTRESULTSDIR)

$(TESTRESULTSDIR)/%.out: $(TESTBINDIR)/%
	$< && RET=$? | tee $@ && exit $(RET)

$(TESTBINDIR)/%: $(TESTDIR)/%.cpp
	g++  $< -o $@
