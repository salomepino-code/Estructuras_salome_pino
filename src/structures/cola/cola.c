
//Cola.c
#include "cola.h"


int colaVacia(Cola cola)
{
	return cola.inicio == cola.fin && cola.cantidad==0;
}
int colaLlena(Cola cola)
{	
	return cola.cantidad==cola.capacidad;
}
//INSERTAR AGREGAR
void agregarCola(Cola *cola,void *dato)
{
	if(colaLlena(*cola))
		return;
	if(colaVacia(*cola))
		cola->inicio = cola->fin = crearNodo(dato);
	else
	{		
		cola->fin->sig = crearNodo(dato);
		cola->fin = cola->fin->sig;	
	}
	cola->cantidad++;
}

void agregarColaNodo(Cola *cola,Nodo *nuevo)
{
	if(colaLlena(*cola))
		return;
	if(colaVacia(*cola))
		cola->inicio = cola->fin = nuevo;
	else
	{		
		cola->fin->sig = nuevo;
		cola->fin = cola->fin->sig;	
	}
	cola->cantidad++;
}

//REMOVER
void* removerCola(Cola *cola)
{
	void *dato=NULL;
	if(colaVacia(*cola))
	{
		return dato;
	}
	cola->cantidad--;
	Nodo *aux = cola->inicio;
	dato = aux->dato;
	cola->inicio = cola->inicio->sig;
	if(!cola->inicio)
		cola->fin = NULL;
	free(aux);
	return dato;
}


Nodo* removerColaNodo(Cola *cola)
{
	Nodo *aux = NULL;
	if(colaVacia(*cola))
	{
		return aux;
	}
	cola->cantidad--;
	aux = cola->inicio;
	cola->inicio = cola->inicio->sig;
	if(!cola->inicio)
		cola->fin = NULL;
	aux->sig = NULL;
	return aux;
}

//MOSTRAR
void imprimirCola(Cola cola)
{
	int cantidad = cola.cantidad;
	printf("\n [%d] Cola:",cantidad);
	for(int i = 0; i<cantidad;i++)
	{
		printf("\n");
		cola.imprimir(cola.inicio->dato);
		agregarColaNodo(&cola, removerColaNodo(&cola) );
	}
}