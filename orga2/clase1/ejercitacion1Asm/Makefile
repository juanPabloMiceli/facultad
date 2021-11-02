
output: main.o suma.o
	gcc -no-pie -o output -m64 main.o suma.o
	

main.o: main.c
	gcc -no-pie -c -m64 main.c -o main.o

suma.o: suma.asm
	nasm -f elf64 suma.asm -o suma.o

clean: 
	rm *.o output

cr:
	nasm -f elf64 suma.asm -o suma.o
	gcc -no-pie -c -m64 main.c -o main.o
	gcc -no-pie -o output -m64 main.o suma.o
	clear
	./output

