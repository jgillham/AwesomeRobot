CXXFLAGS = -Wall
LIBS = /usr/local/lib/libserial.a `pkg-config --libs opencv`
armc:
	g++ -o armc  armctrl.cpp $(CXXFLAGS) $(LIBS) `pkg-config --cflags opencv`
