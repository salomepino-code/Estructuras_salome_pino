#ifndef HEAD_H
#define HEAD_H

#include "../nodos/nodoarbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <pila.h>

#define HEAP_MIN 0
#define HEAP_MAX 1

typedef int (*fn_comparar)(void*,void*);
typedef void (*fn_imprimir)(void*);

typedef struct
{
	unsigned char tipo;
	int cantidad;
	void **datos;
	NodoA *raiz;
	fn_comparar comparar;
	fn_imprimir imprimir;
}Heap;

Heap crearHeap(unsigned char tipo,fn_comparar comparar,fn_imprimir imprimir);
void insertarHeap( Heap *heap,void *dato);
void* eliminarHeap( Heap *heap);
void imprimirHeap( Heap heap);



void heapify_min(Heap *heap,int padre);
void heapify(Heap *heap);
#endif