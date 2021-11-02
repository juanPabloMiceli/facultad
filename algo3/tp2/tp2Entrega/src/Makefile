OBJS= grafo.o main.o hamiltonMasCercano.o hamiltonMenorCosto.o hamiltonAGM.o hamiltonTabuMem.o hamiltonTabuMemEstructura.o types.o
CFLAGS=-Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -Wfloat-conversion -g -F DWARF -O3

all: main

main: $(OBJS)
	g++ $(CFLAGS) -o main $(OBJS)

main.o: main.cpp types.o
	g++ $(CFLAGS) -c -o main.o main.cpp 

grafo.o: grafo.cpp grafo.h types.o
	g++ $(CFLAGS) -c -o grafo.o grafo.cpp

hamiltonMasCercano.o: hamiltonMasCercano.cpp hamiltonMasCercano.h types.o
	g++ $(CFLAGS) -c -o hamiltonMasCercano.o hamiltonMasCercano.cpp

hamiltonMenorCosto.o: hamiltonMenorCosto.cpp hamiltonMenorCosto.h types.o
	g++ $(CFLAGS) -c -o hamiltonMenorCosto.o hamiltonMenorCosto.cpp

hamiltonAGM.o: hamiltonAGM.cpp hamiltonAGM.h types.o
	g++ $(CFLAGS) -c -o hamiltonAGM.o hamiltonAGM.cpp

hamiltonTabuMem.o: hamiltonTabuMem.cpp hamiltonTabuMem.h types.o
	g++ $(CFLAGS) -c -o hamiltonTabuMem.o hamiltonTabuMem.cpp

hamiltonTabuMemEstructura.o: hamiltonTabuMemEstructura.cpp hamiltonTabuMemEstructura.h types.o
	g++ $(CFLAGS) -c -o hamiltonTabuMemEstructura.o hamiltonTabuMemEstructura.cpp

types.o: types.cpp types.h
	g++ $(CFLAGS) -c -o types.o types.cpp

clean:
	-rm *.o
	-rm main