main: main.o lib.o tests.o
	g++ -g -F DWARF -O3 -o main main.o lib.o tests.o

main.o: main.cpp
	g++ -g -F DWARF -O3 -c -o main.o main.cpp

lib.o: lib.cpp
	g++ -g -F DWARF -O3 -c -o lib.o lib.cpp

tests.o: tests.cpp
	g++ -g -F DWARF -O3 -c -o tests.o tests.cpp

clean:
	rm *.o
	rm main