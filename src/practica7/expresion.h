#ifndef EXPRESION_H
#define EXPRESION_H

#include <stdlib.h>
#include <stdio.h>
#include <arbol.h>
#include <iostring.h>

#include "variable.h"


double evaluar(Arbol arbol);
void extraerNodos(NodoA *raiz,NodoA **nodos,int *i);
void asignarMemoria(NodoA **original,int cantidad,int (*comparar)(void*,void*));
void capturarValores(NodoA **original,int cantidad);
void liberarMemoriaValores(NodoA **original,int cantidad);
double calcular(NodoA *raiz);
#endif