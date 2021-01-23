CXX=g++
SOURCES= tools.cpp date.cpp budget.cpp main.cpp
TESTFLAGS= -std=c++1z
TEST_SOURCES= tools.cpp date.cpp budget.cpp UnitTests/utests.cpp

all:
	$(CXX) $(TESTFLAGS) $(CXXFLAGS) -o  main $(SOURCES)
	
test:
	$(CXX) $(TESTFLAGS) -o unit_tests $(TEST_SOURCES)
	./unit_tests
	rm unit_tests

debug:
	$(CXX) $(TESTFLAGS) $(CXXFLAGS) -g $(SOURCES)
	gdb -tui --args a.out
	rm a.out
