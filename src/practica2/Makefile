cflags = -Wall -Werror -std=c99 -O2
dflags = -Wall -Werror -std=c99 -g
includes = -I ../iostring -I ../structures/listadoble
libs = ../../lib -liostring -lListaDoble
source = $(wildcard *.c) 
output = ../../bin/practica2

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
rebuild:
	make -C ..\iostring
	make -C ..\structures\nodos
	make -C ..\structures\listadoble
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"