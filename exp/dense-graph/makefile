SOURCES=$(wildcard src/*.cpp)
OBJS=$(SOURCES:.cpp=.o)

Debug: $(OBJS)
	echo "Sources:"$(SOURCES)
	g++ `pkg-config --libs boost` -o main $(OBJS)

%.o:%.cpp
	g++  `pkg-config --cflags boost` -Iinclude -o $@ -c $<

zip:
	rm -Rf *.zip *.o
	zip -r $@ . -x *.zip -x *.class -x *.ctxt
