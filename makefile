.phony: clean

all: secuencial

secuencial: secuencial.o
	g++ -o $@ $^

secuencial.o: secuencial.cpp

clean:
	rm -f secuencial.o 