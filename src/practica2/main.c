#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listadoble.h"

//Declaraciones

typedef struct {
    unsigned int matricula;
    char         nombre[64];
    int          semestres;
    float        promedio;
} Alumno;

Alumno *crearAlumno(void);
void    imprimirAlumno(void *dato);

int compararMatricula(void *a, void *b);
int compararNombre   (void *a, void *b);
int compararSemestres(void *a, void *b);
int compararPromedio (void *a, void *b);

int  menu      (void);
int  menuCampo (void);

void registrarAlumno (ListaD *lista);
void mostrarAlumnos  (ListaD  lista);
void reordenarAlumnos(ListaD *lista);
void buscarAlumno    (ListaD  lista);
void borrarAlumno    (ListaD *lista);

//Main 

int main(void)
{
    ListaD lista   = inicializarListaD();
    lista.imprimir = imprimirAlumno;
    lista.comparar = compararMatricula;
    lista.liberar  = free;

    int op;
    do {
        op = menu();
        switch (op) {
            case 1: registrarAlumno(&lista); break;
            case 2: mostrarAlumnos(lista);   break;
            case 3: reordenarAlumnos(&lista); break;
            case 4: buscarAlumno(lista);     break;
            case 5: borrarAlumno(&lista);    break;
            case 6: break;
            default: puts("Opcion invalida."); break;
        }
    } while (op != 6);

    borrarListaD(&lista);
    puts("\nFin del programa.");
    return 0;
}

//Implementacion 

static int (*const comparadores[4])(void*, void*) = {
    compararMatricula,
    compararNombre,
    compararSemestres,
    compararPromedio
};

// Alumno

Alumno *crearAlumno(void)
{
    Alumno *a = malloc(sizeof(Alumno));

    printf("Matricula : "); scanf("%u", &a->matricula); getchar();
    printf("Nombre    : "); fgets(a->nombre, 64, stdin);
    a->nombre[strcspn(a->nombre, "\n")] = '\0';
    printf("Semestres : "); scanf("%d", &a->semestres);
    printf("Promedio  : "); scanf("%f", &a->promedio); getchar();

    return a;
}

void imprimirAlumno(void *dato)
{
    Alumno *a = dato;
    printf("Matricula: %u | Nombre: %s | Semestres: %d | Promedio: %.2f",
           a->matricula, a->nombre, a->semestres, a->promedio);
}

// Comparadores

int compararMatricula(void *a, void *b)
{
    return (int)((Alumno*)a)->matricula - (int)((Alumno*)b)->matricula;
}

int compararNombre(void *a, void *b)
{
    return strcmp(((Alumno*)a)->nombre, ((Alumno*)b)->nombre);
}

int compararSemestres(void *a, void *b)
{
    return ((Alumno*)a)->semestres - ((Alumno*)b)->semestres;
}

int compararPromedio(void *a, void *b)
{
    float d = ((Alumno*)a)->promedio - ((Alumno*)b)->promedio;
    return (d > 0) - (d < 0);
}

// Menus

int menu(void)
{
    int op;
    puts("\n===== MENU =====");
    puts("1. Registrar alumno");
    puts("2. Mostrar alumnos");
    puts("3. Reordenar");
    puts("4. Buscar alumno");
    puts("5. Borrar alumno");
    puts("6. Salir");
    printf("Opcion: ");
    scanf("%d", &op); getchar();
    return op;
}

int menuCampo(void)
{
    int op;
    puts("\n1. Matricula");
    puts("2. Nombre");
    puts("3. Semestres");
    puts("4. Promedio");
    printf("Opcion: ");
    scanf("%d", &op); getchar();
    return op;
}

// Operaciones

void registrarAlumno(ListaD *lista)
{
    Alumno *nuevo = crearAlumno();

    int (*compGuardado)(void*, void*) = lista->comparar;
    lista->comparar = compararMatricula;
    NodoD *existe = buscarDatoD(*lista, nuevo);
    lista->comparar = compGuardado;

    if (existe) {
        puts("\nMatricula repetida.");
        free(nuevo);
    } else {
        insertEnOrdenD(lista, nuevo);
    }
}

void mostrarAlumnos(ListaD lista)
{
    int op;
    puts("\n1. Ascendente");
    puts("2. Descendente");
    printf("Opcion: ");
    scanf("%d", &op); getchar();

    (op == 1) ? imprimirListaDIF(lista) : imprimirListaDFI(lista);
}

void reordenarAlumnos(ListaD *lista)
{
    int campo = menuCampo();
    if (campo < 1 || campo > 4) { puts("Opcion invalida."); return; }

    reordenarD(lista, comparadores[campo - 1]);
    puts("\nLista reordenada.");
}

void buscarAlumno(ListaD lista)
{
    Alumno temp = {0};
    int campo = menuCampo();

    switch (campo) {
        case 1: printf("Matricula : "); scanf("%u", &temp.matricula); getchar(); break;
        case 2: printf("Nombre    : "); fgets(temp.nombre, 64, stdin);
                temp.nombre[strcspn(temp.nombre, "\n")] = '\0'; break;
        case 3: printf("Semestres : "); scanf("%d", &temp.semestres); getchar(); break;
        case 4: printf("Promedio  : "); scanf("%f", &temp.promedio);  getchar(); break;
        default: puts("Opcion invalida."); return;
    }

    lista.comparar = comparadores[campo - 1];
    NodoD *encontrado = buscarDatoD(lista, &temp);

    if (encontrado) imprimirAlumno(encontrado->dato);
    else            puts("\nNo encontrado.");
}

void borrarAlumno(ListaD *lista)
{
    Alumno temp;
    printf("Matricula a borrar: ");
    scanf("%u", &temp.matricula); getchar();

    int (*compGuardado)(void*, void*) = lista->comparar;
    lista->comparar = compararMatricula;
    borrarDatoD(lista, &temp);
    lista->comparar = compGuardado;
}