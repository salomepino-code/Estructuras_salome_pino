#ifndef NODO_DOBLE_H
#define NODO_DOBLE_H


#include <stdlib.h>

typedef struct nodod
{
	void *dato;
	struct nodod *sig;
	struct nodod *ant;
}NodoD;

NodoD* crearNodoD(void *dato);

#endif