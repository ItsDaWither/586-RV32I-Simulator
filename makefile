CC = gcc
CFLAGS = -Wall -Werror -g

riscv: riscv.o memory.o
	$(CC) $(CFLAGS) riscv.o memory.o -o riscv

riscv.o: riscv.c
	$(CC) $(CFLAGS) -c riscv.c

memory.o: memory.c memory.h
	$(CC) $(CFLAGS) -c memory.c

clean:
	rm -f riscv riscv.o memory.o
