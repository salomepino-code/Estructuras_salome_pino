#ifndef ALUMNO_H
#define ALUMNO_H

#include <stdio.h>
#include <stdlib.h>
#include "../iostring/iostring.h"

#define LEN 64

typedef struct
{
	unsigned int matricula;
	char nombre[LEN];
	int semestre;
	float promedio;
}Alumno;

Alumno* crearAlumno(void);
void imprimirAlumno(void *dato);
//comparar
// NEGATIVO si datoA < datoB
// CERO si datoA == datoB
// POSITIVO si datoA > datoB
int compararMatricula(void *datoA,void *datoB);
int compararNombre(void *datoA,void *datoB);
int compararSemestre(void *datoA,void *datoB);
int compararPromedio(void *datoA,void *datoB);
int compararAlumno(void *datoA,void *datoB);
#endif