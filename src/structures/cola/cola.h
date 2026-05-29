
//Cola.h
#ifndef COLA_H
#define COLA_H

#include <stdio.h>
#include <stdio.h>
#include <nodo.h>

typedef void (*fn_imprimir)(void*);

typedef struct
{
	Nodo *inicio;
	Nodo *fin;
	int cantidad;
	int capacidad;
	fn_imprimir imprimir;
}Cola;

int colaVacia(Cola);
int colaLlena(Cola);
//INSERTAR AGREGAR
void agregarCola(Cola*,void*);
void agregarColaNodo(Cola*,Nodo*);

//REMOVER
void* removerCola(Cola*);
Nodo* removerColaNodo(Cola*);
//MOSTRAR
void imprimirCola(Cola);

//ELIMINAR


#endif