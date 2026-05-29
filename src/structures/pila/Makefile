cflags = -Wall -Werror -std=c99 -O2 -c
dflags = -Wall -Werror -std=c99 -g
outNodo = ../nodos/nodo.o
source = $(wildcard *.c)
source_o = $(wildcard *.o)
output = ../../../lib/libPila.a

build :
	gcc $(cflags) $(source) 
	ar rcs $(output) $(source_o) $(outNodo)
	@echo "Compilo Exitosamente!!!"