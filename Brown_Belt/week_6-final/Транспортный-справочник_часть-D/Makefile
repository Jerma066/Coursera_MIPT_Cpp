CXX=g++
SOURCES= json.cpp main.cpp
TESTFLAGS= -std=c++1z
TEST_SOURCES= json.cpp transport_d.cpp

all:
	$(CXX) $(TESTFLAGS) $(CXXFLAGS) -o  main $(SOURCES)
	
test:
	$(CXX) $(TESTFLAGS) -o ete_test $(TEST_SOURCES)
	./ete_test < EteTests/json1.dat
	rm ete_test

debug:
	$(CXX) $(TESTFLAGS) -g $(TEST_SOURCES)
	gdb -tui --args a.out
