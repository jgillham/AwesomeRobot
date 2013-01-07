PYSRC=$(wildcard *.py)

TESTRESULTS=$(PYSRC:%.py=test%.out)

run:
	python GoState.py
Debug: Settings

Release: Settings

TestAll: Settings $(TESTRESULTS)

Settings: settings.py

settings.py: ../../inc/Settings.h
	grep "#define ROBOT_" $< | sed "s/\#define\ ROBOT_\(\w*\)\s\(.*\)/\1 = \2/g" > $@

test%.out: %.py
	python -m doctest -v $< && RET=$? | tee $@ && exit $(RET)

