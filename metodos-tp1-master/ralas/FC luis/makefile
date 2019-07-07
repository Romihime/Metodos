all: solucionFC

solucionFC: solucionFC.o matrixFC.o
	g++ -O3 -g -Wall -std=c++0x -o $@ $^

%.o: %.cpp
	g++ -O3 -g -Wall -std=c++0x -c -o $@ $^

clean:
	rm -rf *.o
	rm -rf *.out
	rm -rf solucionFC
