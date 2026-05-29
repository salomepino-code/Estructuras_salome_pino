#include <stdio.h>
#include <stdlib.h>
#include <pila.h>
#include <iostring.h>
#include "Laberinto.h"


int main(void)
{
    Laberinto lab = crear_laberinto();
	Coordenada *punto;
	//Movimientos mov;
	Coordenada origen = {1,1}; 
	Coordenada destino = {25,24};
	unsigned int nuevasCoor = 0;	
	inputEnteroSinSigno("\n Nuevas coordenadas? (1:SI 0:NO) : ",&nuevasCoor);
	if(nuevasCoor)
	{
		inputEntero("\n Captura Origen X: ",&origen.x);
		inputEntero(" Captura Origen Y: ",&origen.y);
		inputEntero("\n Captura Destino X: ",&destino.x);
		inputEntero(" Captura Destino Y: ",&destino.y);
	}
	setOrigen(lab,origen);
	setDestino(lab,destino);
	imprimirLab(lab);
	printf("\n");
	
	Pila pila = {NULL,0,-1,imprimirCoordenada,free};
	//PUSH INICIAL DEL ORIGEN
	punto = crearCoordenada(origen.x,origen.y);
	pushDato(&pila,punto);
	
	//CICLO

	while( !pilaVacia(pila))
	{
		punto = (Coordenada*)peekPila(pila);
		Movimientos mov;
		mov = movimientosPosibles(lab,*punto);		
		//SI LLEGO
		if (lab[punto->x][punto->y+1] == 'B' ||
		lab[punto->x][punto->y-1] == 'B' ||
		lab[punto->x+1][punto->y] == 'B' ||
		lab[punto->x-1][punto->y] == 'B')
		{
			lab[punto->x][punto->y] = '.';
			imprimirLab(lab);
			printf("\nLlegaste al destino\n ");
			break;
			}
		//REGRESAR
		else if(bloqueado(mov))
		{
			lab[punto->x][punto->y] = 'o'; 
			free( popDato(&pila) );
		}
			
		//MOVERTE
		
		//DERECHA
		else if( mov.right == 1)
		{
			lab[punto->x][punto->y] = '.';
			punto = crearCoordenada(punto->x,punto->y+1);
			pushDato(&pila,punto);
		}
		//IZQUIERDA
		else if( mov.left == 1)
		{
			lab[punto->x][punto->y] = '.';
			punto = crearCoordenada(punto->x,punto->y-1);
			pushDato(&pila,punto);
		}
		//ABAJO
		else if( mov.down == 1)
		{
			lab[punto->x][punto->y] = '.';
			punto = crearCoordenada(punto->x+1,punto->y);
			pushDato(&pila,punto);
			
		}
		//ARRIBA
		else if ( mov.up == 1)
		{
			lab[punto->x][punto->y] = '.';
			punto = crearCoordenada(punto->x-1,punto->y);
			pushDato(&pila,punto);
			
		}
	}
 	
	liberarLaberinto(lab);
    printf("\n\n FIN DE PROGRAMA\n\n");
    return 0;
}


