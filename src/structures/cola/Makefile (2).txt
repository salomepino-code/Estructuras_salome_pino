cflags = -Wall -Werror -std=c99 -O2 -c
dflags = -Wall -Werror -std=c99 -g
sourceNodo = ../nodos/nodo.o
source = $(wildcard *.c)
source_o = $(wildcard *.o)
output = ../../../lib/libCola.a

includes = -I ../nodos 
sourceNodo = ../nodos/nodo.o
build :
	gcc $(cflags) $(source) $(includes) 
	ar rcs $(output) $(source_o) $(sourceNodo)
	@echo "Compilo Exitosamente!!!"