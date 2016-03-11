GTESTLIB = /Users/dtaliun/Documents/gtest/googletest/cmake/test/
GTESTINCS = /Users/dtaliun/Documents/gtest/googletest/include/

AUXLIBS = ../../FileReader/src/*.o
AUXDIRS = ../../FileReader/src

APPLIBS = ../src/*.o
APPDIRS = ../src

CXX = g++
CXXFLAGS = -std=c++11 -Wall -L/opt/local/lib/ -lz -L$(GTESTLIB) -lgtest
INCS = -I$(GTESTINCS)

OBJECTS = VCFReaderTest.o Main_TestAll.o

.PHONY: all auxlibs applibs

all: auxlibs applibs testAll

auxlibs:
	@for auxdir in $(AUXDIRS); do \
		(cd $${auxdir} && make -j 4) || exit 1; \
	done
	
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