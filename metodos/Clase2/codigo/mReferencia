ASM = $(wildcard *.asm)
ASM_O = $(ASM:.asm=.o)

main: ${ASM} *c
	make ${ASM_O}
	gcc *.c *.o -o ejec -lm -no-pie

%.o: %.c
	gcc -lm -no-pie -c -o $@ $<

%.o: %.asm
	nasm -f elf64 $< -g

clean:
	-rm -f *.o ejec