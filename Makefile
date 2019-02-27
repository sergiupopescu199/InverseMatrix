CFLAGS=-ansi -Wall -Werror -Wpedantic

all:		main.exe

main.exe:	inversa.o
			gcc ${CFLAGS} -o main.exe inversa.o

inversa.o:	inversa.c
			gcc -c ${CFLAGS} inversa.c

.PHONY:	clean

clean:
		-rm *.exe *.o 