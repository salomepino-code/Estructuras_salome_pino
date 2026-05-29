#include "Laberinto.h"

Coordenada* crearCoordenada(int x,int y)
{
	Coordenada *nueva = malloc(sizeof(Coordenada));
	nueva->x=x;
	nueva->y=y;
	return nueva;
}

void imprimirCoordenada(void *dato)
{
	Coordenada *a = dato;
	printf("[%-2d,%-2d]", a->x,a->y);
}

int compararCoordenada(void *a,void *b)
{
	Coordenada *aa=a,*bb=b;
	if(aa->x==bb->x && aa->y==bb->y)
		return 1;
	return 0;
}

