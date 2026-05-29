
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <iostring.h>
#include <arbol.h>
#include "variable.h"
#include "expresion.h"

#define MAX 100

void abortar(void);
void ordenIterativo(NodoA *raiz,void (*imprimir)(void*));
void imprimirDoubleDouble(void *);

Arbol postfixAArbol(char *postfix);
int esOperando(char c);
int esOperador(char c);
void infixAPostfix(char *infix, char *postfix);
int verificarParentesis(char *cadena);
double calcular(NodoA *raiz);

int main(void)
{
	Arbol arbol;
	arbol.raiz = NULL;
	arbol.imprimir = &imprimirVariable;
	arbol.comparar = &compararVariable;
	arbol.liberar = &free;
	
	
	char infix[MAX];
    char postfix[MAX];
    memset(postfix, 0, MAX);
	int opcion;
	
    do
    {
        printf("\n===== MENU =====");
        printf("\n0. Ingresar expresion");
        printf("\n1. Imprimir arbol");
        printf("\n2. Evaluar");
        printf("\n3. Salir");
        printf("\nOpcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
           case 0:
                if (arbol.raiz != NULL)
                {
                    eliminarArbol(&arbol);
                    arbol.raiz = NULL;
                    arbol.cantidad = 0;
                    arbol.imprimir = &imprimirVariable;
                    arbol.comparar = &compararVariable;
                    arbol.liberar = &free;
                    memset(infix, 0, MAX);
                    memset(postfix, 0, MAX);
                }
                printf("\n Ingresa expresion infix: ");
                scanf("%s", infix);

                if (!verificarParentesis(infix))
                {
                    printf("\n ERROR: parentesis no balanceados\n");
                    memset(infix, 0, MAX);
                    break;
                }

                infixAPostfix(infix, postfix);
                printf("\n Postfix: %s\n", postfix);
                arbol = postfixAArbol(postfix);
                printf("\n Expresion ingresada correctamente.\n");
                break;

            case 1:
                if (arbol.raiz == NULL)
                {
                    printf("\n No hay expresion. Use opcion 0 primero.\n");
                    break;
                }
                printf("\n ARBOL:\n");
                imprimirArbol(arbol);
                break;

            case 2:
                if (arbol.raiz == NULL)
                {
                    printf("\n No hay expresion. Use opcion 0 primero.\n");
                    break;
                }
                evaluar(arbol);
                break;

            case 3:
                if (arbol.raiz != NULL)
                    eliminarArbol(&arbol);
                printf("\n\n FIN DE PROGRAMA\n");
                break; 
        }
    }while (opcion != 3);

    return 0;
}


void imprimirDoubleDouble(void *ptr)
{
	double **ptrdouble= ptr;	
	if(!ptrdouble)	
	{		
		printf("null ") ;
		return;
	}
	printf("%lf ",**ptrdouble); 
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

//
Arbol postfixAArbol(char *postfix)
{
    Arbol arbol;
    arbol.raiz = NULL;
    arbol.cantidad = 0;
    arbol.imprimir = &imprimirVariable;
    arbol.comparar = &compararVariable;
    arbol.liberar = &free;

    Pila pila = {NULL, 0, -1, NULL, NULL};
    int i = 0;

    while (postfix[i] != '\0')
    {
        char c = postfix[i];
        NodoA *nodo = crearNodoA(crearVariable(c));
        arbol.cantidad++;

        if (esOperando(c))
        {
            pushDato(&pila, nodo);
        }
        else if (esOperador(c))
        {
            if (pila.cantidad < 2)
            {
                printf("\n ERROR: operador '%c' sin dos operandos\n", c);
                exit(1);
            }
            nodo->dch = popDato(&pila);
            nodo->izq = popDato(&pila);
            pushDato(&pila, nodo);
        }
        i++;
    }

    if (pila.cantidad != 1)
    {
        printf("\n ERROR: expresion invalida\n");
        exit(1);
    }

    arbol.raiz = popDato(&pila);
    return arbol;
}

double calcular(NodoA *raiz)
{
    if (!raiz)
        return 0;

    // es operando → devolver su valor
    if (precedencia(raiz->dato) == OPERANDO)
        return **((Variable *)raiz->dato)->v;

    // es operador → resolver hijos primero
    double izq = calcular(raiz->izq);
    double dch = calcular(raiz->dch);

    char op = ((Variable *)raiz->dato)->c;

    switch (op)
    {
        case '+': return izq + dch;
        case '-': return izq - dch;
        case '*': return izq * dch;
        case '/':
            if (dch == 0)
            {
                printf("\n ERROR: division entre cero\n");
                exit(1);
            }
            return izq / dch;
        case '^': return pow(izq, dch);
    }
    return 0;
}
