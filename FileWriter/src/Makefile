CXX = g++
CXXFLAGS = -std=c++11 -Wall -O3
INCS = 

all: WriterException.o WriterCreateException.o WriterOpenException.o WriterCloseException.o WriterWriteException.o Writer.o TextWriter.o GzipWriter.o WriterFactory.o

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCS) -c -o $@ $<
	
clean:
	rm -f *.o 