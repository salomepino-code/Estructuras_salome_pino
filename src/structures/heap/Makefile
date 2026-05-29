cflags = -Wall -Werror -std=c99 -O2 -c
dflags = -Wall -Werror-std=c99 -g
sources = ../nodos/nodoarbol.o ../pila/pila.o
includes = -I ../pila
source = $(wildcard *.c)
source_o = $(wildcard *.o)
output = ../../../lib/libHeap.a

build :
	gcc $(cflags) $(source) $(includes)
	ar rcs $(output) $(source_o) $(sources) 
	@echo "Compilo Exitosamente!!!"