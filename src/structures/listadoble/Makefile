cflags = -Wall -Werror -pedantic -std=c99 -O2 -c
dflags = -Wall -Werror -pedantic -std=c99 -g
outNodo = ../nodos/nododoble.o
source = $(wildcard *.c)
source_o = $(wildcard *.o)
output = ../../../lib/libListaDoble.a

build :
	gcc $(cflags) $(source) 
	ar rcs $(output) $(source_o) $(outNodo)
	@echo "Compilo Exitosamente!!!"