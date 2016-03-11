CXX = g++
CXXFLAGS = -std=c++11 -Wall -O3
INCS =

all: CommandLineException.o \
	DuplicatedOptionException.o \
	InvalidOptionException.o \
	UnknownOptionException.o \
	CommandLine.o

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCS) -c -o $@ $<
	
clean:
	rm -f *.o 