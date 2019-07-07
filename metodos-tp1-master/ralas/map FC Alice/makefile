all: solucion_cambiada

solucion_cambiada: solucion_cambiada.o matrix_cambiada.o
	g++ -O3 -g -Wall -std=c++0x -o $@ $^

%.o: %.cpp
	g++ -O3 -g -Wall -std=c++0x -c -o $@ $^

clean:
	rm -rf *.o
	rm -rf *.out
	rm -rf solucion_cambiada
