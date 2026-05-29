#include "Laberinto.h"


Movimientos movimientosPosibles(Laberinto lab,Coordenada punto)
{
	Movimientos movimientos = {0,0,0,0};
	//ARRIBA
	if( lab[punto.x-1][punto.y] == '*')
		movimientos.up = 1;
	//ABAJO
	if( lab[punto.x+1][punto.y] == '*')
		movimientos.down = 1;
	//DERECHA
	if( lab[punto.x][punto.y+1] == '*')
		movimientos.right = 1;
	//IZQUIERDA
	if( lab[punto.x][punto.y-1] == '*')
		movimientos.left = 1;
	return movimientos;	
}


void imprimirMovimientos(Movimientos movimientos)
{	
	printf("\n");
	//ARRIBA
	if( movimientos.up == 1)
		printf(" ARRIBA");
	//ABAJO
	if( movimientos.down == 1)
		printf(" ABAJO");
	//DERECHA
	if( movimientos.right == 1)
		printf(" DERECHA");
	//IZQUIERDA
	if( movimientos.left == 1)
		printf(" IZQUIERDA");
	
}


int bloqueado(Movimientos mov)
{
	return mov.up == 0 && mov.up == mov.down && mov.up==mov.left && mov.up==mov.right;
}
