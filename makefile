.phony: clean
LDFLAGS=-fopenmp
CPPFLAGS=-std=c++11

all: secuencial openmp

secuencial: secuencial.o
	$(CXX) -o $@ $^

secuencial.o: secuencial.cpp

openmp: openmp.o
	$(CXX) -o $@ $^ $(LDFLAGS)

openmp.o: openmp.cpp

clean:
	rm -f *.o 
	rm -f secuencial 
	rm -f openmp
