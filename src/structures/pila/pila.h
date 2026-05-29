#ifndef PILA_H
#define PILA_H

#include <stdio.h>
#include "..\nodos\nodo.h"

typedef struct
{
	Nodo *cima;
	int cantidad;
	int capacidad;
	void (*imprimir)(void*);
	void (*liberar)(void*);
}Pila;

//PEEK
void* peekPila(Pila pila);

//VERIFICIACION
int pilaVacia(Pila pila);
int pilaLlena(Pila pila);
//DATOS
void pushDato(Pila *pila,void *dato);
void* popDato(Pila *pila);
//NODOS
void pushNodo(Pila *pila,Nodo *nodo);
Nodo* popNodo(Pila *pila);
//VACIAR/ELIMINAR PILA
void vaciarPila(Pila *pila);
void eliminarPila(Pila *pila);
//IMPRIMIR
void imprimirPila(Pila pila);

#endif