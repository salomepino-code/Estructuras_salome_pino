#include "heap.h"

int compararInt(void *a, void *b)
{
    return *(int*)a - *(int*)b;
}

void imprimirInt(void *dato)
{
    printf("%d", *(int*)dato);
}


void _dibujarHeap(Heap h, int i, char* prefijo, int esIzq, int esRaiz)
{
    if (i >= h.cantidad) return;

    int izq = 2*i+1;
    int der = 2*i+2;
    char nuevoPrefijo[256];

    if (der < h.cantidad) {
        if (esRaiz)
            snprintf(nuevoPrefijo, sizeof(nuevoPrefijo), "|       ");
        else if (esIzq)
            snprintf(nuevoPrefijo, sizeof(nuevoPrefijo), "%s|       ", prefijo);
        else
            snprintf(nuevoPrefijo, sizeof(nuevoPrefijo), "%s        ", prefijo);
        _dibujarHeap(h, der, nuevoPrefijo, 0, 0);
    }

    if (esRaiz) {
        h.imprimir(h.datos[i]);
        printf("\n");
    } else {
        printf("%s%s ", prefijo, esIzq ? "|---I" : "|----R");
        h.imprimir(h.datos[i]);
        printf("\n");
    }

    if (izq < h.cantidad) {
        if (esRaiz)
            snprintf(nuevoPrefijo, sizeof(nuevoPrefijo), "        ");
        else if (esIzq)
            snprintf(nuevoPrefijo, sizeof(nuevoPrefijo), "%s        ", prefijo);
        else
            snprintf(nuevoPrefijo, sizeof(nuevoPrefijo), "%s|       ", prefijo);
        _dibujarHeap(h, izq, nuevoPrefijo, 1, 0);
    }
}

void imprimirArbolHeap(Heap heap)
{
    printf("\n Imprimir el Arbol\n");
    if (!heap.cantidad) { printf("VACIO\n"); return; }
    _dibujarHeap(heap, 0, "", 0, 1);
}

int main()
{
    Heap heap = crearHeap(HEAP_MAX, compararInt, imprimirInt);

    int valores[] = {7, 4, 5, 2, 1, 3};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++)
        insertarHeap(&heap, &valores[i]);

    imprimirHeap(heap);
	imprimirArbolHeap(heap);

    return 0;
}