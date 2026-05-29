
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostring.h>
#include <heap.h>

typedef struct {
    char nombre[50];
    int paginas;
} Archivo;

int compararArchivo(void *a, void *b);
void imprimirArchivo(void *a);
Archivo *crearArchivo(void);
void imprimirArbol(NodoA *nodo, int nivel, fn_imprimir imprimir);
void reconstruirArbol(Heap *heap);
void imprimirArbolHeap(Heap heap);
void eliminarEnPosicion(Heap *heap, int pos);
void vaciarHeap(Heap *heap);
void mostrarEstado(Heap *heap, const char *etiqueta);
void mostrarPreview(Heap *heap);
void mostrarColaCompleta(Heap *heap);
void opCambiarPrioridad(Heap *heap);
void opMostrarCola(Heap *heap);
void opAgregarArchivo(Heap *heap);
void opProcesarArchivo(Heap *heap);
void opEliminarArchivo(Heap *heap);
void opEliminarTodos(Heap *heap);

int main(void)
{
    srand((unsigned)time(NULL));

    Heap heap = crearHeap(HEAP_MIN, compararArchivo, imprimirArchivo);

    for (int i = 0; i < 5; i++)
        insertarHeap(&heap, crearArchivo());

    int opcion;

    do
    {
        mostrarPreview(&heap);

        printf("\n===== MENU =====");
        printf("\n0. Cambiar prioridad");
        printf("\n1. Mostrar cola de impresion");
        printf("\n2. Agregar archivo");
        printf("\n3. Procesar / imprimir archivo");
        printf("\n4. Eliminar archivo");
        printf("\n5. Eliminar todos los archivos");
        printf("\n6. Terminar programa");
        printf("\nOpcion: ");

        scanf("%d", &opcion);

        switch (opcion)
        {
            case 0:
                opCambiarPrioridad(&heap);
                break;

            case 1:
                opMostrarCola(&heap);
                break;

            case 2:
                opAgregarArchivo(&heap);
                break;

            case 3:
                opProcesarArchivo(&heap);
                break;

            case 4:
                opEliminarArchivo(&heap);
                break;

            case 5:
                opEliminarTodos(&heap);
                break;

            case 6:
                vaciarHeap(&heap);
                printf("\n Saliendo del programa...\n");
                break;

            default:
                printf("\n Opcion invalida.\n");
        }

    } while (opcion != 6);

    return 0;
}

int compararArchivo(void *a, void *b)
{
    Archivo *aa = a;
    Archivo *bb = b;

    if (aa->paginas == bb->paginas)
        return 0;

    if (aa->paginas < bb->paginas)
        return -1;

    return 1;
}

void imprimirArchivo(void *a)
{
    Archivo *aa = a;
    printf("%-20s %3d pag.", aa->nombre, aa->paginas);
}

Archivo *crearArchivo(void)
{
    static int c = 1;

    const char *p[] = {
        "Doc", "Reporte", "Tarea", "Carta",
        "Factura", "Manual", "Informe", "Memo"
    };

    Archivo *a = malloc(sizeof(Archivo));

    snprintf(a->nombre, sizeof(a->nombre), "%s_%03d", p[rand() % 8], c++);

    a->paginas = rand() % 200 + 1;

    return a;
}

void imprimirArbol(NodoA *nodo, int nivel, fn_imprimir imprimir)
{
    int i;

    if (!nodo)
        return;

    printf(" ");
    imprimir(nodo->dato);

    if (nodo->dch)
    {
        printf("\n");

        for (i = 0; i <= nivel; i++)
            printf(i == nivel ? " |____R " : " |      ");

        imprimirArbol(nodo->dch, nivel + 1, imprimir);
    }

    if (nodo->izq)
    {
        printf("\n");

        for (i = 0; i <= nivel; i++)
            printf(" |      ");

        printf("\n");

        for (i = 0; i <= nivel; i++)
            printf(i == nivel ? " |____L " : " |      ");

        imprimirArbol(nodo->izq, nivel + 1, imprimir);
    }
}

void reconstruirArbol(Heap *heap)
{
    NodoA **stack = malloc(sizeof(NodoA *) * (heap->cantidad + 1) * 2);
    int top = 0;

    if (heap->raiz)
        stack[top++] = heap->raiz;

    while (top)
    {
        NodoA *n = stack[--top];

        if (n->izq)
            stack[top++] = n->izq;

        if (n->dch)
            stack[top++] = n->dch;

        free(n);
    }

    free(stack);

    heap->raiz = NULL;

    if (!heap->cantidad)
        return;

    NodoA **nodos = malloc(sizeof(NodoA *) * heap->cantidad);

    for (int i = 0; i < heap->cantidad; i++)
        nodos[i] = crearNodoA(heap->datos[i]);

    for (int i = 0; i < heap->cantidad; i++)
    {
        if (2 * i + 1 < heap->cantidad)
            nodos[i]->izq = nodos[2 * i + 1];

        if (2 * i + 2 < heap->cantidad)
            nodos[i]->dch = nodos[2 * i + 2];
    }

    heap->raiz = nodos[0];

    free(nodos);
}

void imprimirArbolHeap(Heap heap)
{
    printf("\n Arbol:\n  ");

    if (heap.raiz)
        imprimirArbol(heap.raiz, 0, heap.imprimir);
    else
        printf("VACIO");

    printf("\n");
}

void eliminarEnPosicion(Heap *heap, int pos)
{
    if (pos < 0 || pos >= heap->cantidad)
        return;

    heap->datos[pos] = heap->datos[heap->cantidad - 1];

    heap->cantidad--;

    if (heap->cantidad > 0)
    {
        void **aux = realloc(heap->datos, heap->cantidad * sizeof(void *));

        if (aux != NULL)
            heap->datos = aux;

        heapify(heap);
    }
    else
    {
        free(heap->datos);
        heap->datos = NULL;
    }

    reconstruirArbol(heap);
}

void vaciarHeap(Heap *heap)
{
    for (int i = 0; i < heap->cantidad; i++)
        free(heap->datos[i]);

    free(heap->datos);

    heap->datos = NULL;
    heap->cantidad = 0;

    reconstruirArbol(heap);
}

void mostrarEstado(Heap *heap, const char *etiqueta)
{
    reconstruirArbol(heap);

    printf("\n----- %s -----", etiqueta);

    printf("\n Prioridad: %s | Elementos: %d",
           heap->tipo == HEAP_MIN ? "MINIMO" : "MAXIMO",
           heap->cantidad);

    imprimirArbolHeap(*heap);

    imprimirHeap(*heap);
}

void mostrarPreview(Heap *heap)
{
    reconstruirArbol(heap);

    printf("\n===== COLA DE IMPRESION (top 5) =====");

    if (!heap->cantidad)
    {
        printf("\n (vacia)");
    }
    else
    {
        int mostrar = heap->cantidad < 5 ? heap->cantidad : 5;

        for (int i = 0; i < mostrar; i++)
        {
            printf("\n [%d] ", i);
            imprimirArchivo(heap->datos[i]);
        }

        if (heap->cantidad > 5)
            printf("\n ... y %d mas en cola", heap->cantidad - 5);
    }

    printf("\n Prioridad: %s",
           heap->tipo == HEAP_MIN ? "MINIMO" : "MAXIMO");

    printf("\n=====================================\n");
}

void mostrarColaCompleta(Heap *heap)
{
    printf("\n----- COLA COMPLETA -----");

    if (!heap->cantidad)
    {
        printf("\n (vacia)");
        return;
    }

    for (int i = 0; i < heap->cantidad; i++)
    {
        printf("\n [%d] ", i);
        imprimirArchivo(heap->datos[i]);
    }
}

void opCambiarPrioridad(Heap *heap)
{
    mostrarEstado(heap, "ANTES de cambiar prioridad");

    heap->tipo = heap->tipo == HEAP_MIN ? HEAP_MAX : HEAP_MIN;

    heapify(heap);

    printf("\n >> Prioridad: %s",
           heap->tipo == HEAP_MIN ? "MINIMO" : "MAXIMO");

    mostrarEstado(heap, "DESPUES de cambiar prioridad");
}

void opMostrarCola(Heap *heap)
{
    mostrarEstado(heap, "COLA DE IMPRESION");

    mostrarColaCompleta(heap);
}

void opAgregarArchivo(Heap *heap)
{
    mostrarEstado(heap, "ANTES de agregar");

    Archivo *nuevo = crearArchivo();

    printf("\n Generado: %-20s %d paginas",
           nuevo->nombre,
           nuevo->paginas);

    insertarHeap(heap, nuevo);

    mostrarEstado(heap, "DESPUES de agregar");
}

void opProcesarArchivo(Heap *heap)
{
    if (!heap->cantidad)
    {
        printf("\n Cola vacia.\n");
        return;
    }

    mostrarEstado(heap, "ANTES de procesar");

    Archivo *proc = eliminarHeap(heap);

    printf("\n IMPRIMIENDO: %-20s (%d paginas)",
           proc->nombre,
           proc->paginas);

    free(proc);

    mostrarEstado(heap, "DESPUES de procesar");
}

void opEliminarArchivo(Heap *heap)
{
    if (!heap->cantidad)
    {
        printf("\n Cola vacia.\n");
        return;
    }

    mostrarColaCompleta(heap);

    printf("\n Indice a eliminar: ");

    int idx;
    scanf("%d", &idx);

    if (idx < 0 || idx >= heap->cantidad)
    {
        printf("\n Invalido.\n");
        return;
    }

    Archivo *a = heap->datos[idx];

    printf("\n Eliminando: %-20s (%d paginas)",
           a->nombre,
           a->paginas);

    mostrarEstado(heap, "ANTES de eliminar");

    free(a);

    eliminarEnPosicion(heap, idx);

    mostrarEstado(heap, "DESPUES de eliminar");
}

void opEliminarTodos(Heap *heap)
{
    if (!heap->cantidad)
    {
        printf("\n Ya vacia.\n");
        return;
    }

    mostrarEstado(heap, "ANTES de vaciar");

    vaciarHeap(heap);

    printf("\n Cola vaciada.");

    mostrarEstado(heap, "DESPUES de vaciar");
}