CC = gcc
CFLAGS = -Wall -Werror -g

riscv: riscv.c
	$(CC) $(CFLAGS) -o riscv riscv.c

clean:
	rm -f riscv

