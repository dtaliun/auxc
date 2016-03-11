CXX = g++
CXXFLAGS = -std=c++11 -Wall -O3
INCS =

all: VCFException.o \
	Field.o \
	ChromField.o \
	PosField.o \
	IdField.o \
	RefField.o \
	AltField.o \
	QualField.o \
	FilterField.o \
	InfoField.o \
	FormatField.o \
	GenotypeField.o \
	VCFReader.o \
	Meta.o \
	Variant.o

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCS) -c -o $@ $<
	
clean:
