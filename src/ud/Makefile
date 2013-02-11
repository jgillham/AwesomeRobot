PYSRC=$(wildcard *.py)

TESTRESULTS=$(PYSRC:%.py=test%.out)

run:
	python modes.py
Debug: Settings

Release: Settings

TestAll: Settings $(TESTRESULTS)

Settings: settings.py

settings.py: ../ld/Settings.h
	grep "#define ROBOT_" $< | sed "s/\#define\ ROBOT_\(\w*\)\s\(.*\)/\1 = \2/g" > $@

test%.out: %.py
	python -m doctest -v $< && RET=$? | tee $@ && exit $(RET)

