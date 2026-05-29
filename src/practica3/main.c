#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <pila.h>
#include <iostring.h>

#define MAX 100

int palindromo(char *cadena);
int verificarParentesis(char *cadena);

int main(void)
{
    char *cadena = NULL;
    int opcion = 0;

    do {
        printf("\n===== MENU =====");
        printf("\n 1. Palindromo");
        printf("\n 2. Verificacion de parentesis");
        printf("\n 3. Terminar ejecucion");
        printf("\n Opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
            case 1:
                inputCadenaDinamica("\n Captura cadena: ", &cadena, MAX);
                printf(" Es palindromo: %s", palindromo(cadena) ? "SI" : "NO");
                free(cadena);
                cadena = NULL;
                break;

            case 2:
                inputCadenaDinamica("\n Captura expresion: ", &cadena, MAX);
                printf(" Parentesis correctos: %s", verificarParentesis(cadena) ? "SI" : "NO");
                free(cadena);
                cadena = NULL;
                break;

            case 3:
                printf("\n FIN DE PROGRAMA\n");
                break;

            default:
                printf("\n Opcion invalida.");
                break;
        }

    } while (opcion != 3);

    return 0;
}

int palindromo(char *cadena)
{
    Pila pila = {NULL, 0, MAX, NULL, NULL};
    int len = strlen(cadena);

    // Quitar salto de linea si existe
    if (cadena[len - 1] == '\n') 
		cadena[--len] = '\0';

    // Push de cada caracter ignorando espacios
    for (int i = 0; i < len; i++)
    {
        if (cadena[i] == ' ') continue;
        char *c = malloc(sizeof(char));
        *c = tolower(cadena[i]);
        pushDato(&pila, c);
    }

    // Comparar con pop ignorando espacios
    for (int i = 0; i < len; i++)
    {
        if (cadena[i] == ' ') continue;
        char *cima = (char *)popDato(&pila);
        if (tolower(cadena[i]) != *cima)
        {
            free(cima);
            eliminarPila(&pila); // liberar lo que quede
            return 0;            
        }
        free(cima);
    }

    return 1; 
}

int verificarParentesis(char *cadena)
{
    Pila pila = {NULL, 0, MAX, NULL, NULL};
    int len = strlen(cadena);

    // Quitar salto de linea si existe
    if (cadena[len - 1] == '\n') 
		cadena[--len] = '\0';

    for (int i = 0; i < len; i++)
    {
        char c = cadena[i];

        // Si es apertura -> push
        if (c == '(' || c == '{' || c == '[')
        {
            char *nuevo = malloc(sizeof(char));
            *nuevo = c;
            pushDato(&pila, nuevo);
        }
        // Si es cierre -> verificar
        else if (c == ')' || c == '}' || c == ']')
        {
            // Cierre sin apertura
            if (pilaVacia(pila))
            {
                return 0;
            }

            char tope = *((char *)popDato(&pila));

            // Cierre no coincide con apertura
            if ((c == ')' && tope != '(') ||
                (c == '}' && tope != '{') ||
                (c == ']' && tope != '['))
            {
                eliminarPila(&pila);
                return 0;
            }
        }
    }

    // Termino cadena y hay algo en la pila
    if (!pilaVacia(pila))
    {
        eliminarPila(&pila);
        return 0;
    }

    return 1;
}