all: output main.o vectores.o 

output: main.o vectores.o
	gcc -no-pie -o output -m64 main.o vectores.o
	

main.o: main.c
	gcc -no-pie -c -m64 main.c -o main.o

vectores.o: vectores.asm
	nasm -f elf64 -g -F DWARF vectores.asm

clean: 
	rm *.o output

valgrind:
	valgrind --leak-check=full ./output


