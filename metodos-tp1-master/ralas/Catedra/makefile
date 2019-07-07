all: main

main: main.o matrix.o
	g++ -g -Wall -std=c++0x -o $@ $^

test: test_matrix.o matrix.o
	g++ -g -Wall -std=c++0x -o $@ $^

solucion: solucion.o matrix.o
	g++ -O3 -g -Wall -std=c++0x -o $@ $^

solucionFC: solucionFC.o matrixFC.o
	g++ -O3 -g -Wall -std=c++0x -o $@ $^

solucion_cambiada: solucion_cambiada.o matrix_cambiada.o
	g++ -O3 -g -Wall -std=c++0x -o $@ $^

%.o: %.cpp
	g++ -O3 -g -Wall -std=c++0x -c -o $@ $^

clean:
	rm -rf *.o
	rm -rf main test solucion solucion_cambiada solucionFC ejecutable
