.phony: clean

all: secuencial

secuencial: secuencial.o
	g++ -std=c++14 -o $@ $^

secuencial.o: secuencial.cpp

clean:
	rm -f secuencial.o 
