#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pila.h>

#define MAX 100

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

void infixAPostfix(char *infix, char *postfix)
{
    Pila pila = {NULL, 0, MAX, NULL, NULL};
    int i = 0;

    while (infix[i] != '\0')
    {
        char c = infix[i];

        if (esOperando(c))
        {
            int len = strlen(postfix);
            postfix[len] = c;
            postfix[len + 1] = '\0';
        }
        else if (c == '(')
        {
            char *copia = malloc(sizeof(char));
            *copia = c;
            Nodo *nuevo = crearNodo(copia);
            pushNodo(&pila, nuevo);
        }
        else if (c == ')')
        {
            while (!pilaVacia(pila))
            {
                char *tope = (char*)peekPila(pila);
                if (*tope == '(')
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
            Nodo *basura = popNodo(&pila);
            free(basura->dato);
            free(basura);
        }
        else if (esOperador(c))
        {
            while (!pilaVacia(pila))
            {
                char *tope = (char*)peekPila(pila);
                if (*tope == '(')
                    break;
                Variable temp;
                temp.c = *tope;
                Variable curr;
                curr.c = c;
                if (compararPrecedencia(&temp, &curr) < 0)
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
            char *copia = malloc(sizeof(char));
            *copia = c;
            Nodo *nuevo = crearNodo(copia);
            pushNodo(&pila, nuevo);
        }
        i++;
    }

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