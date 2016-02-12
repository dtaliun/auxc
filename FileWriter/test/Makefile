GTEST_LIB = /Users/dtaliun/Documents/gtest/googletest/cmake/test/
GTEST_INCS = /Users/dtaliun/Documents/gtest/googletest/include/

CXX = g++
CXXFLAGS = -std=c++11 -Wall -L/opt/local/lib/ -lz -L$(GTEST_LIB) -lgtest
INCS = -I$(GTEST_INCS)

OBJECTS =  ../src/WriterException.o ../src/WriterCreateException.o ../src/WriterOpenException.o ../src/WriterCloseException.o ../src/WriterWriteException.o ../src/Writer.o ../src/TextWriter.o ../src/GzipWriter.o ../src/WriterFactory.o WriterFactoryTest.o TextWriterTest.o GzipWriterTest.o Main_TestAll.o

testAll: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCS) -o $@ $(OBJECTS)
	
.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCS) -c -o $@ $<
	
clean:
	rm -f testAll *.o  ../src/*.o