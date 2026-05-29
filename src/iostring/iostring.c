#include "iostring.h"


void clear_buffer(void)
{
	char c;
	while( (c = getchar()) != '\n' && c !=EOF);
}

void remover_salto(char *cadena)
{
	int i = -1;
	while(cadena[++i]!='\n' && cadena[i]!='\0');
	cadena[i] = '\0';
}

unsigned int inputEnteroSinSigno(char *mensaje,unsigned int *valor)
{
	int resultado;
	printf("%s",mensaje);
	resultado = scanf("%u",valor);
	clear_buffer();
	return resultado;
}

int inputEntero(char *mensaje,int *valor)
{
	int resultado;
	printf("%s",mensaje);
	resultado = scanf("%d",valor);
	clear_buffer();
	return resultado;
}

int inputFloat(char *mensaje,float *valor)
{
	int resultado;
	printf("%s",mensaje);
	resultado = scanf("%f",valor);
	clear_buffer();
	return resultado;
}
int inputDouble(char *mensaje,double *valor)
{	
	int resultado;
	printf("%s",mensaje);
	resultado = scanf("%lf",valor);
	clear_buffer();
	return resultado;
}
int inputChar(char *mensaje,char *valor)
{	
	int resultado;
	printf("%s",mensaje);
	resultado = scanf("%c",valor);
	clear_buffer();
	return resultado;	
}

int inputCadena(char *mensaje,char *cadena,int longitud)
{	
	char *res;
	int resultado;
	if( longitud >= 2 )
		cadena[longitud-2] = '\n';	
	else 
		return 0;
	printf("%s",mensaje);
	res = fgets(cadena,longitud,stdin);
	if(cadena[longitud-2] != '\n')
		clear_buffer();	
	remover_salto(cadena);
	resultado = (res) ? 1:0;
	return resultado;	
}


int inputCadenaDinamica(char *mensaje,char **cadena,int max)
{
	int res;
	if(*cadena)
		free(*cadena);
	*cadena = malloc(sizeof(char) * max +1 );
	if(!cadena)
		return 0;	
	res = inputCadena(mensaje,*cadena,max); 
	if(!res)
		free(*cadena);
	else
	{
		char *aux = NULL;
		int size;
		size = strlen(*cadena)+1;
		while(!aux)
			aux = realloc(*cadena,sizeof(char)*size);
		*cadena = aux;
	}
	return res;
}

char* cadenaDinamica(const char * cadena)
{
	char *dinamica = NULL;
	int size;
	size = strlen(cadena)+1;
	while(!dinamica)
		dinamica = malloc(sizeof(char)*size);
	strcpy(dinamica,cadena);
	return dinamica;
}


char mayuscula(char caracter)
{
	if( caracter>='a' && caracter<='z')
		return caracter-32;
	return caracter;
}

int strcmpIC(char *cadA,char *cadB)
{
	int i;
	char a,b;	
	for( i = 0; cadA[i]!='\0' && cadB[i]!='\0';i++)
	{
		a = mayuscula(cadA[i]);
		b = mayuscula(cadB[i]);
		if( a == b)
			continue;
		else if( a < b)
			return -1;
		else
			return 1;
	}
	if(cadA[i]==cadB[i])
		return 0;
	else if(cadA[i]=='\0')
		return -1;
	else
		return 1;
}