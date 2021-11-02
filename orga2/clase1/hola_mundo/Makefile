
holaMundo: holaMundo.o
	ld -o holaMundo holaMundo.o

holaMundo.o: holaMundo.asm
	nasm -f elf64 -g -F DWARF holaMundo.asm

clean: 
	rm *.o holaMundo


