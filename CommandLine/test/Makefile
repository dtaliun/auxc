GTEST_LIB = /Users/dtaliun/Documents/gtest/googletest/cmake/test/
GTEST_INCS = /Users/dtaliun/Documents/gtest/googletest/include/

APPLIBS = ../src/*.o
APPDIRS = ../src

CXX = g++
CXXFLAGS = -std=c++11 -Wall -L$(GTEST_LIB) -lgtest
INCS = -I$(GTEST_INCS)

OBJECTS = CommandLineTest.o Main_TestAll.o

.PHONY: all applibs

all: applibs testAll

applibs:
	@for appdir in $(APPDIRS); do \
		(cd $${appdir} && make -j 4) || exit 1; \
	done

testAll: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCS) -o $@ $(OBJECTS) $(AUXLIBS) $(APPLIBS)
	
.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCS) -c -o $@ $<
	
clean:
	rm -f testAll *.o  ../src/*.o
