#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H

#include <stdio.h>
#include "../nodos/nododoble.h"

typedef struct 
{
	NodoD *inicio;
	NodoD *fin;
	int cant;
	void (*imprimir)(void *datoA);
	int (*comparar)(void *datoA,void *dataB);
	void (*liberar)(void *datoA);
}ListaD;

//IMPLEMENTADAS
void imprimirListaDIF(ListaD lista);
void imprimirListaDFI(ListaD lista);
void insertarFinalD(ListaD*,void*);

void borrarInicioD(ListaD *lista);
void borrarListaD(ListaD *);

ListaD inicializarListaD(void);
//BUSCAR
NodoD* buscarDatoD(ListaD lista,void *dato);
NodoD* buscarDatoEspecificoD(ListaD lista,void *dato,int (*comparar)(void*,void*));
//INSERTAR
void insertEnOrdenD(ListaD *lista,void *dato);
void insertarInicioD(ListaD*,void*);
int insertarEnD( ListaD * lista, void *dato,int index);
//ELIMINAR
int borrarEnD( ListaD *lista, int index);
void borrarFinD(ListaD *lista);
void borrarDatoD(ListaD *lista,void *dato);
void reordenarD(ListaD *lista, int (*comparar)(void*,void*));


#endif