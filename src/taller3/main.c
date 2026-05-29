#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <time.h>
#include <iostring.h>
#include <arbol.h>

void abortar(void);
int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);
void imprimirNodo(void*);
void imprimirResultado(Resultado resultado);

void extraerMitades(int *arr1,int *arr2,int longitud,int *i);

void myprintf(char *msg,char *formato,...);

void ordenIterativo(NodoA *raiz,void (*imprimir)(void*));

int main(void)
{
	Arbol arbol;
	arbol.raiz = NULL;
	arbol.cantidad = 0;
	arbol.imprimir = &imprimirEntero;
	arbol.comparar = &compararEntero;
	arbol.liberar = &free;
	
	insertarArbol(&arbol, crearEntero(7));
	insertarArbol(&arbol, crearEntero(4));
	insertarArbol(&arbol, crearEntero(2));
	insertarArbol(&arbol, crearEntero(8));
	insertarArbol(&arbol, crearEntero(9));
	insertarArbol(&arbol, crearEntero(6));
	insertarArbol(&arbol, crearEntero(1));
	insertarArbol(&arbol, crearEntero(5));
	
	printf("\n");
	imprimirArbol(arbol);
	
	printf("\n");	
	imprimirOrden(arbol, ORDEN);
	
	printf("\n");
	ordenIterativo(arbol.raiz,imprimirNodo);
	

	// BUSCAR Y MOSTRAR PADRE + RAMA
	int valor;
	printf("\n ingresa valor a buscar: ");
	scanf("%d", &valor);
	void *dato = buscarEnArbol(arbol, &valor);
	if(dato)
		printf("\n ENCONTRADO");
	else
		printf("\n NO ENCONTRADO");
	
	imprimirResultado(buscarNodoEnArbol(arbol, &valor));
	
	printf("\n\nAntes del flip:  ");
	imprimirOrden(arbol, ORDEN);

	invertirArbol(&arbol);

	printf("\nDespues del flip: ");
	
	imprimirArbol(arbol);
	printf("\n");
	imprimirOrden(arbol, ORDEN);
	printf("\n");
	
	eliminarArbol(&arbol); 
	printf("\n\n FIN DE PROGRAMA\n");
	
	int arr1[9] = {1,4,5,6,7,8,9,10,11};
	int arr2[9];
	int i = 0;
	extraerMitades(arr1, arr2, 9, &i);
	printf("\n");
	for(i = 0; i < 9; i++)
		printf(" %d", arr2[i]);
	
	return 0;
}
void ordenIterativo(NodoA *raiz,void (*imprimir)(void*))
{
	Pila pila = {NULL,0,-1,imprimir,NULL};
	if(!raiz)
		return;
	NodoA* aux = raiz;
	while( aux || !pilaVacia(pila))
	{			
		while(aux)
		{
			pushDato(&pila,aux);	
			aux = aux->izq;
		}		
		aux = popDato(&pila);
		imprimir(aux);		
		printf(" ");		
		aux= aux->dch;
	}	
	vaciarPila(&pila);
}

void abortar(void)
{
	char c = 'e';
	if( (c=getchar()) == 'e')
		exit(0);
}

void extraerMitades(int *arr1,int *arr2,int longitud,int *i)
{
	if(longitud <= 0)
		return;
	int mitad = longitud/2;
	arr2[*i] = arr1[mitad];
	(*i)++;
	extraerMitades(arr1, arr2, mitad, i);
	extraerMitades(arr1+mitad+1, arr2, longitud-1-mitad, i);	
}
void imprimirResultado(Resultado resultado)
{
	if(resultado.nodo)
	{
		if(resultado.padre)
		{
			printf("\n PADRE: ");
			imprimirEntero(resultado.padre->dato);
			printf("\n RAMA: %s", (resultado.rama) ? "DERECHA" : "IZQUIERDA");
		}
		else
		printf("\n Nodo: ");
		imprimirEntero(resultado.nodo->dato); 	
	
	}
	else
		printf("\n NODO NO ENCONTRADO");
}
int* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}
int compararEntero(void*a,void*b)
{
	int *aa = a, *bb = b;
	if(*aa == *bb) return 0;
	else if(*aa < *bb) return -1;
	else return 1;
}
void imprimirEntero(void *a)
{
	int *aa = a;
	printf("%d", *aa);
}
void imprimirNodo(void *a)
{
	NodoA *aa = a;
	imprimirEntero(aa->dato);
}
void myprintf(char* msg,char *formato,...)
{
	va_list args;
	va_start(args, formato);
	printf("\n %s ", msg);
	char *ptr = formato;
	while(*ptr != '\0')
	{
		switch(*ptr)
		{
			case 'd':
				printf("%d ",va_arg(args, int));
				break;
			case 'c':
				printf("%c ",va_arg(args, int));				
				break;
			case 'f':
				printf("%f ",va_arg(args, double));				
				break;
			case 'x':
				printf("%x ",va_arg(args, Arbol*));				
				break;
		}
		ptr++;
	}
	va_end(args);
}