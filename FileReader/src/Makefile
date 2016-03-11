CXX = g++
CXXFLAGS = -std=c++11 -Wall -O3
INCS =

all: ReaderException.o \
	ReaderCreateException.o \
	ReaderOpenException.o \
	ReaderCloseException.o \
	ReaderReadException.o \
	Reader.o \
	TextReader.o \
	GzipReader.o \
	ReaderFactory.o

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCS) -c -o $@ $<
	
clean:
	rm -f *.o 