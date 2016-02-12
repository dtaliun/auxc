GTEST_LIB = /Users/dtaliun/Documents/gtest/googletest/cmake/test/
GTEST_INCS = /Users/dtaliun/Documents/gtest/googletest/include/

CXX = g++
CXXFLAGS = -std=c++11 -Wall -L$(GTEST_LIB) -lgtest
INCS = -I$(GTEST_INCS)

OBJECTS = ../src/CommandLineException.o ../src/DuplicatedOptionException.o ../src/InvalidOptionException.o ../src/UnknownOptionException.o ../src/CommandLine.o CommandLineTest.o Main_TestAll.o

testAll: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCS) -o $@ $(OBJECTS)
	
.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCS) -c -o $@ $<
	
clean:
	rm -f testAll *.o  ../src/*.o