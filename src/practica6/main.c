
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

#define MAX 100

void infixAPostfix(char *infix, char *postfix);
int verificarParentesis(char *cadena);
int precedencia(char c);
int compararPrecedencia(char a, char b);
int esOperador(char c);
int esOperando(char c);

int main()
{
    char infix[MAX];
    char postfix[MAX] = "";

    printf("\nCaptura expresion infix: ");
    scanf(" %s", infix);

    if (!verificarParentesis(infix))
    {
        printf("\nERROR: Parentesis incorrectos\n");
        return 0;
    }

    infixAPostfix(infix, postfix);

    printf("\nPostfix: %s", postfix);
    printf("\nFIN");
    return 0;
}
void infixAPostfix(char *infix, char *postfix)
{
    Pila pila = {NULL, 0, MAX, NULL, NULL};
    int i = 0;

    while (infix[i] != '\0')
    {
        char c = infix[i];

        // si es operando → agregar directo al postfix 
        if (esOperando(c))
        {
            int len = strlen(postfix);
            postfix[len] = c;
            postfix[len + 1] = '\0';
        }
        // si es '(' hacer push a pila
        else if (c == '(')
        {
            char *copia = malloc(sizeof(char));
            *copia = c;
            Nodo *nuevo = crearNodo(copia);
            pushNodo(&pila, nuevo);
        }
        // si es ')' sacar operadores hasta encontrar '('
        else if (c == ')')
        {
            while (!pilaVacia(pila))
            {
                char *tope = (char*)peekPila(pila); 
                if (*tope == '(') // lo encontro
					break;            

                Nodo *nodo = popNodo(&pila);
                char *dato = (char*)nodo->dato;
                char valor = *dato;

                int len = strlen(postfix);
                postfix[len] = valor;
                postfix[len + 1] = '\0';

                free(dato);
                free(nodo);
            }
            // sacar el '(' de la pila sin pasarlo al postfix
            Nodo *basura = popNodo(&pila);
            free(basura->dato);
            free(basura);
        }
        // si es operador, comparar precedencia con cima de pila
        else if (esOperador(c))
        {
            // sacar operadores de la pila mientras:
            // 1. la pila no este vacia
            // 2. la cima no sea '(' (parentesis resetea precedencia)
            // 3. la cima tenga mayor o igual precedencia al operador actual
            while (!pilaVacia(pila))
            {
                char *tope = (char*)peekPila(pila); 
                if (*tope == '(') 
					break;
                if (compararPrecedencia(*tope, c) < 0) 
					break;

                // sacar operador de cima y pasarlo al postfix
                Nodo *nodo = popNodo(&pila);
                char *dato = (char*)nodo->dato;
                char valor = *dato;

                int len = strlen(postfix);
                postfix[len] = valor;
                postfix[len + 1] = '\0';

                free(dato);
                free(nodo);
            }

            // push del operador actual
            char *copia = malloc(sizeof(char));
            *copia = c;
            Nodo *nuevo = crearNodo(copia);
            pushNodo(&pila, nuevo);
        }

        i++;
    }

    // al terminar el recorrido → vaciar toda la pila al postfix
    while (!pilaVacia(pila))
    {
        Nodo *nodo = popNodo(&pila);
        char *dato = (char*)nodo->dato;
        char valor = *dato;

        int len = strlen(postfix);
        postfix[len] = valor;
        postfix[len + 1] = '\0';

        free(dato);
        free(nodo);
    }
}

int verificarParentesis(char *cadena)
{
    Pila pila = {NULL, 0, MAX, NULL, NULL};
    int i = 0;

    while (cadena[i] != '\0')
    {
        char c = cadena[i];

        if (c == '(')
        {
            char *copia = malloc(sizeof(char));
            *copia = c;
            Nodo *nuevo = crearNodo(copia);
            pushNodo(&pila, nuevo);
        }
    
        else if (c == ')')
        {
            
            if (pilaVacia(pila))
                return 0;

            Nodo *tope = popNodo(&pila);
            free(tope->dato);
            free(tope);
        }

        i++;
    }

    if (!pilaVacia(pila))
        return 0;

    return 1; 
}

int precedencia(char c)
{
    if (c == '+' || c == '-') 
		return 1; 
    if (c == '*' || c == '/') 
		return 2; 
    if (c == '^')             
		return 3; 
    return 0;
}

int compararPrecedencia(char a, char b)
{
    int pa = precedencia(a);
    int pb = precedencia(b);
    if (pa < pb) return -1;
    if (pa > pb) return 1;
    return 0; 
	
}

int esOperador(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int esOperando(char c)
{
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9');
}