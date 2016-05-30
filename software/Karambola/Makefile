CXX      = g++

CXXFLAGS  = -Wall -O2 -DNDEBUG
BINARY = karambola

VERSION_NUMBER = 1.5-NJP

LDFLAGS= -lgsl -lgslcblas
CXXFLAGS += -DVERSION_NUMBER=$(VERSION_NUMBER)

LIBOBJ = \
	lib/Triangulation.o \
	minkowski_functions/calculate_wx00.o \
	minkowski_functions/calculate_w010.o \
	minkowski_functions/calculate_w110.o \
	minkowski_functions/calculate_w210.o \
	minkowski_functions/calculate_w310.o \
	minkowski_functions/calculate_w020.o \
	minkowski_functions/calculate_w120.o \
	minkowski_functions/calculate_w220.o \
	minkowski_functions/calculate_w320.o \
	minkowski_functions/calculate_w102.o \
	minkowski_functions/calculate_w202.o \
	lib/check_surface.o \
	print_functions/print_explanations.o \
	print_functions/print_CompWiseScalarMinkValResultType.o \
	print_functions/print_CompWiseVectorMinkValResultType.o \
	print_functions/print_CompWiseMatrixMinkValResultType.o \
	print_functions/write_surface_props_to_file.o \
	print_functions/write_CompWiseMatrixMinkValResultType_to_file.o \
	print_functions/write_CompWiseVectorMinkValResultType_to_file.o \
	print_functions/write_CompWiseScalarMinkValResultType_to_file.o \
	print_functions/write_CompWiseEigenSystemMinkValResultType_to_file.o \
	lib/MinkValResultType.o \
	lib/calculate_eigensystem.o \
	lib/readpoly.o \
	lib/tensor.o \
	lib/gsleig.o 


HDR = *.h lib/*.h minkowski_functions/*.h print_functions/*.h Makefile

default: $(LIBOBJ) $(BINARY).o $(BINARY)

$(BINARY): $(HDR) $(BINARY).o
	$(CXX) -o $(BINARY) $(BINARY).o $(LIBOBJ) $(LDFLAGS)

%.o: %.cpp $(HDR)
	$(CXX) $(CXXFLAGS) -o $*.o -c $<

clean:
	find . -name \*.o -delete
	rm -f $(BINARY)

