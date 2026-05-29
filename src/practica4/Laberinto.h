#ifndef LABERINTO_H
#define LABERINTO_H

#include <stdio.h>
#include <stdlib.h>


#define REN 27
#define COL 26


typedef unsigned char **Laberinto;//?

typedef struct
{
	int x,y;
}Coordenada;

typedef struct
{
	int up,down,left,right;
}Movimientos;



//FUNCIONES DEL LABERINTO
Laberinto crear_laberinto(void);
void liberarLaberinto(Laberinto lab);
void imprimirLab(Laberinto lab);
void setOrigen(Laberinto lab,Coordenada origen);
void setDestino(Laberinto lab,Coordenada destino);

//FUNCIONES DE COORDENADAS
Coordenada* crearCoordenada(int x,int y);
int compararCoordenada(void *a,void *b);
void imprimirCoordenada(void *dato);



//FUNCIONES DE MOVIMIENTOS
Movimientos movimientosPosibles(Laberinto lab,Coordenada punto);
int bloqueado(Movimientos mov);
void imprimirMovimientos(Movimientos movimientos);

#endif
