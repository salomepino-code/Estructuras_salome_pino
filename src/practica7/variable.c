#include "variable.h"

Variable* crearVariable(char c)
{
	Variable* nuevo=calloc(1,sizeof(Variable));
	nuevo->c=c;
	return nuevo;
}

int compararVariable(void *a,void *b)
{
	char aa = ((Variable*)a)->c;
	char bb = ((Variable*)b)->c;
	if( aa ==  bb )
		return 0;
	else if( aa <  bb )
		return -1;
	else 
		return 1;
}

void imprimirVariable(void *a)
{
	printf("%c",((Variable*)a)->c);
}

void imprimirValor(void *a)
{
	if( ((Variable*)a)->v )
		printf("%lf",**((Variable*)a)->v);
	else
		printf("null");
}


int precedencia(void *a)
{
	char c = ((Variable*)a)->c;
	switch(c)
	{
		case '+':case '-':
			return 1;
		case '*':case '/':
			return 2;			
		case '^':
			return 3;			
		case '(':
			return -1;
	}
	return 0;
}

int compararPrecedencia(void *a,void *b)
{
	if( precedencia(a)>precedencia(b) )
		return 1;
	else if( precedencia(a)<precedencia(b) )
		return -1;
	else return 0;
}