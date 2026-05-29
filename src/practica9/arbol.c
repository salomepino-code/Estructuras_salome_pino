#include "arbol.h"



Resultado buscarNodoEnArbol(Arbol arbol,void *dato)
{
	Resultado result = {NULL,NULL,NULL,DERECHA};
	NodoA *raiz = arbol.raiz;	
	while(raiz)
	{
		if(arbol.comparar(raiz->dato,dato) == 0)
		{
			result.nodo = raiz;
			result.dato = raiz->dato;	
			break;
		}
		else
		{ 
			result.padre = raiz;
			if(arbol.comparar(raiz->dato,dato) > 0)  
			{
				result.rama = IZQUIERDA;
				raiz = raiz->izq;		
			}				
			else
			{
				result.rama = DERECHA;
				raiz = raiz->dch;
			}
		}
	}
	return result;
}
	

void* buscarEnArbol(Arbol arbol,void *dato)
{
	void *result = NULL;
	NodoA *raiz = arbol.raiz;
	
	while(raiz)
	{
		if(arbol.comparar(raiz->dato,dato) == 0)
		{
			result = raiz->dato;
			break;
		}
		else if(arbol.comparar(raiz->dato,dato) > 0 )
			raiz = raiz->izq;
		else
			raiz = raiz->dch;
	}
	return result;
}	

void invertirRamas(NodoA *raiz)
{
	if(!raiz)
		return;
	NodoA *aux = raiz->izq;
	raiz->izq = raiz->dch;
	raiz->dch = aux;
	invertirRamas(raiz->izq);
	invertirRamas(raiz->dch);
}

void invertirArbol(Arbol *arbol)
{
	invertirRamas(arbol->raiz);
}


void insertarArbolOrdenado(NodoA *raiz,void *dato,int (*comparar)(void*,void*))
{
	if(comparar(dato,raiz->dato)<=0)
	{
		//IZQUIERDA
		if(!raiz->izq)			
			raiz->izq = crearNodoA(dato);
		else if(!raiz->dch && comparar(dato,raiz->dato)==0)			
			raiz->dch = crearNodoA(dato);
		else			
			insertarArbolOrdenado(raiz->izq,dato,comparar);
	}
	else
	{
		//DERECHA
		if(raiz->dch)
			insertarArbolOrdenado(raiz->dch,dato,comparar);
		else
			raiz->dch = crearNodoA(dato);
	}
}



void insertarArbol(Arbol *arbol,void *dato)
{
	if(!arbol->raiz)
		arbol->raiz = crearNodoA(dato);
	else
		insertarArbolOrdenado(arbol->raiz, dato, arbol->comparar);
	arbol->cantidad++;
}



void imprimir_arbol(NodoA* nodo, int nivel,void (*imprimir)(void*))
{
    int i;
    if (nodo != NULL)
        {
        printf(" ");
		imprimir(nodo->dato);
        if(nodo->dch)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->dch, nivel + 1,imprimir);
        }
        if(nodo->izq)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
                //printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->izq, nivel + 1,imprimir);
        }
    }
}

void imprimirArbol(Arbol arbol)
{
	imprimir_arbol(arbol.raiz,0,arbol.imprimir);
}

void preorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
		printf(" ");
		imprimir(raiz->dato);
		preorden(raiz->izq, imprimir);
		preorden(raiz->dch, imprimir);
}
	


void orden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	orden(raiz->izq, imprimir);
	printf(" ");
	imprimir(raiz->dato);
	printf("\n");
	orden(raiz->dch, imprimir);
}

 
void inverso(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	inverso(raiz->dch, imprimir);
	printf(" ");
	imprimir(raiz->dato);
	inverso(raiz->dch, imprimir);
	
}

void postorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	postorden(raiz->izq, imprimir);
	postorden(raiz->dch, imprimir);
	printf(" ");
	imprimir(raiz->dato);
}


void imprimirOrden(Arbol arbol,int opcion)
{
	switch(opcion)
	{
		case PREORDEN: 
			preorden(arbol.raiz,arbol.imprimir);
			break;
		case ORDEN: 
			orden(arbol.raiz,arbol.imprimir);
			break;
		case INVERSO: 
			inverso(arbol.raiz,arbol.imprimir);
			break;
		case POSTORDEN: 
			postorden(arbol.raiz,arbol.imprimir);
			break;
	}
}


void eliminar_NodosA(NodoA *raiz,void (*liberar)(void*))
{
	if(!raiz)
		return;
	eliminar_NodosA(raiz->izq, liberar);
	eliminar_NodosA(raiz->dch, liberar);
	
	if(liberar)
		liberar(raiz->dato);
	free(raiz);
}


void eliminarArbol(Arbol *arbol)
{
	eliminar_NodosA( arbol->raiz, arbol->liberar);
	arbol->raiz = NULL;
	arbol->cantidad = 0;
}

void vaciarArbol(Arbol *arbol)
{
	eliminar_NodosA( arbol->raiz,NULL);
	arbol->raiz = NULL;
	arbol->cantidad = 0;
}

