CC=c99
CFLAGS=-Wall -Wextra -pedantic -O0 -g -lm -Wno-unused-variable -Wno-unused-parameter -no-pie
CFLAGS=-g -lm -no-pie
NASM=nasm
NASMFLAGS=-f elf64 -g -F DWARF 

all: main imagen.o

main: main.c imagen.o
	$(CC) $(CFLAGS) $^ -o $@

# tester: tester.c lib_c.o lib_asm.o
# 	$(CC) $(CFLAGS) $^ -o $@

# lib_c.o: lib.c
# 	$(CC) $(CFLAGS) -c $< -o $@

imagen.o: imagen.asm
	$(NASM) $(NASMFLAGS) $< -o $@


clean:
	rm -f *.o
	rm -f imagen

