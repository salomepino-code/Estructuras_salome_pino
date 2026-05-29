#include <stdio.h>
#include <iostring.h>
#include <pila.h>

void imprimirEntero(void *dato);
void ordenarPila(Pila *pila, int (*comparar)(void*, void*));
int compararEnteros(void *a, void *b);

int main()
{
	Pila pila = {NULL,0,7,imprimirEntero,NULL};
	
	int arreglo[7];
	
	for(int i=0; i<7;i++)
	{	
	    printf("\n ingresa numero %d:", i+1);
		scanf("%d", &arreglo[i]);
		pushDato(&pila,&arreglo[i]);
	}
	
	ordenarPila(&pila, compararEnteros);
	imprimirPila(pila);
	

	return 0;
}

void imprimirEntero(void *dato)
{
	int *datoA = dato;
	printf(" %d",*datoA);
}

void ordenarPila(Pila *pila, int (*comparar)(void*, void*))
{
    Pila aux = {NULL, 0, pila->capacidad, pila->imprimir, pila->liberar};
    while(!pilaVacia(*pila))
    {
        // 1. Sacar el elemento actual de la pila original
        void *actual = popDato(pila);
        
        // 2. Mover elementos de aux a original mientras no sea el lugar correcto
        while(!pilaVacia(aux) && comparar(actual,aux.cima->dato))
        {
            pushDato(pila, popDato(&aux));
        }
        
        // 3. Insertar el elemento actual en aux 
        pushDato(&aux,actual);
    }
    
    // 4. Pasar todo de aux a la original
    while(!pilaVacia(aux))
    {
        pushDato(pila, popDato(&aux));
    }
}
int compararEnteros(void *a, void *b)
{
    int *x = a;
    int *y = b;
    return *x > *y; // devuelve 1 si a > b
}
