#ifndef VARIABLE_H
#define VARIABLE_H

#include <stdio.h>
#include <stdlib.h>

#define OPERANDO 0

typedef struct
{
	char c;
	double **v;
}Variable;

Variable* crearVariable(char c);
void imprimirVariable(void *a);
void imprimirValor(void *a);
int compararVariable(void *a,void *b);

int compararPrecedencia(void *p_a,void *p_b);
int precedencia(void *a);

#endif