#include "Laberinto.h"










Laberinto crear_laberinto(void)
{
    int i,j;
    char *tmp = 
"xxxxxxxxxxxxxxxxxxxxxxxxxx\
xAx*****x****************x\
x*xxx*x*x*xxxxxxxxx*xxxx*x\
x*****x*x******x**x****x*x\
xxxxxxx*xxxxxx*xx*xxxx*xxx\
x*****x*x****x*x****xx***x\
x*xxx*x*xxxx*x*x*xxxxx*x*x\
x***x*x****x*****xxxxxxx*x\
xxx*x*xxxx*xxxxxxx****x**x\
x*x*x***xx****xx***xx*x*xx\
x*x*x*x*xxxxx**x*xxxx*x**x\
x*x*x*x***x*xx*x****x*xx*x\
x*x*x*xxx****x*x*xx*x****x\
x*x*x*xxxxxxxx*x**x*xxxx*x\
x***x********x*xx*x*x****x\
x*xxxxxxxxxx*x**xxx*x*xxxx\
x***x******x**x*****x**x*x\
xxx*x*xxxxxxx*xxxxxxxx*x*x\
x*x*x*******x****xx****x*x\
x*x*x*xxxxx*xxxx*xx*xxxx*x\
x*x*x****xx***x**xx*x****x\
x*x*xxxxxxx*x**x*xx*x*x*xx\
x*x*********xx*x*xx*xxx*xx\
x*xxxxxxxxxxx**x*********x\
x***x***x***x*xxxxxxxxxx*x\
x*x***x***x*************Bx\
xxxxxxxxxxxxxxxxxxxxxxxxxx\0";

 
    
    Laberinto lab;
    lab = (unsigned char**) malloc(sizeof(unsigned char *)*REN);//?
    
    for(i=0;i<REN;i++)
    {
        lab[i] = (unsigned char*) malloc(sizeof(unsigned char)*COL);
    }
    
    for(i=0;i<REN;i++)
    {
        //printf("\n\r"); r?
        for(j=0;j<COL;j++)
        {
            //printf("%c",tmp[(i*COL)+j]);?
            lab[i][j] = tmp[(i*COL)+j];
        }   
    }
    return lab;
}

void liberarLaberinto(Laberinto lab)
{
	for(int i = 0; i<REN;i++)
		free(lab[i]);
	free(lab);
}


void imprimirLab(Laberinto lab)
{
	int i,j;
	for(i=0;i<REN;i++)
    {
        printf("\n\r");
        for(j=0;j<COL;j++)
        {
            if(lab[i][j]=='*')printf("  ");
			else printf("%c ",lab[i][j]);
        }   
    }
}


void setAoB(Laberinto lab,Coordenada punto,char caracter)//?
{
	for(int i=0;i<REN;i++)
    {
        for(int j=0;j<COL;j++)
        {
			if(lab[i][j]==caracter)
				lab[i][j]='*';
			if(i == punto.x && j== punto.y)				
				lab[i][j]=caracter;
        }   
    }
}

void setOrigen(Laberinto lab,Coordenada origen)
{
	setAoB(lab,origen,'A');
}

void setDestino(Laberinto lab,Coordenada destino)
{
	setAoB(lab,destino,'B');
}
