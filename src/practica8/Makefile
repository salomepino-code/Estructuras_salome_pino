cflags = -Wall -Werror -std=c99 -O2 
dflags = -Wall -Werror -std=c99 -g
includes = -I ../iostring -I ../structures/nodos -I ../structures/heap -I ../structures/pila
libs = ../../lib -liostring -lHeap
source = $(wildcard *.c) 
output = ../../bin/practica8

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
rebuild:
	make -C ..\structures\arbol
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
run :
	$(output).exe