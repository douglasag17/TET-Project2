.phony: clean

all: secuencial

secuencial: secuencial.o
	g++ -o $@ $^ -std=c++14

secuencial.o: secuencial.cpp

clean:
	rm -f secuencial.o secuencial
