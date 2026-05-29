
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostring.h>
#include "heap.h"

int compararInt(void *a, void *b)
{
    return *(int*)a - *(int*)b;
}

void imprimirInt(void *dato)
{
    printf("%d", *(int*)dato);
}

int main()
{
    Heap heap = crearHeap(HEAP_MAX, compararInt, imprimirInt);

    int valores[] = {7, 4, 5, 2, 1, 3};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++)
        insertarHeap(&heap, &valores[i]);

    imprimirHeap(heap);

    return 0;
}