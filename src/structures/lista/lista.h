
//LISTA.h
#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdio.h>
#include "../nodos/nodo.h"


typedef struct
{
	Nodo *inicio;
	Nodo *fin;
	int cantidad;
	void (*imprimir)(void*); //APUNTADOR A FUNCION
	int (*comparar)(void*,void*);
	void (*liberar)(void *);
}Lista;

typedef struct
{
	Nodo *ante;
	Nodo *enco;
	void *dato;	
}Resultado;

Resultado buscar(Lista lista,void *dato);
void imprimirResultado(Lista lista,Resultado resultado);
void imprimirLista(Lista lista);

//INSERTAR AGREGAR
void agregarFinal(Lista *lista,void *dato);
void agregarEnOrden(Lista *lista,void *dato);
void insertarInicio( Lista * lista, void *dato);
int insertarEn( Lista * lista, void *dato,int index);

//ELIMINAR
int eliminarEn( Lista *lista, int index);
void eliminarInicio(Lista *lista);
void eliminarFinal(Lista *lista);
void eliminarDato(Lista *lista,void *dato);

//REMOVER
void* removerInicio(Lista *lista);

void reordenar(Lista *lista, int (*comparar)(void*,void*));
#endif