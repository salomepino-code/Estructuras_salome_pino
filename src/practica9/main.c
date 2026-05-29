#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "HashQ.h"
#include "Libro.h"
#include "arbol.h"

/* ============================================================
   FUNCIONES DE FOLDING (generacion de clave numerica)
   ============================================================ */

// Folding para ISBN: suma bloques de 4 digitos del string
int folding_isbn(void *vlibro)
{
    Libro *libro = (Libro *)vlibro;
    char *s = libro->isbn;
    int suma = 0, bloque = 0, i = 0, k = 0;
    while (s[i] != '\0')
    {
        if (s[i] != '-')
        {
            bloque = bloque * 10 + (s[i] - '0');
            k++;
            if (k == 4) { suma += bloque; bloque = 0; k = 0; }
        }
        i++;
    }
    if (k > 0) suma += bloque;
    return suma < 0 ? -suma : suma;
}

// Folding para titulo: suma bloques de 4 chars convertidos a numero
int folding_titulo(void *vlibro)
{
    Libro *libro = (Libro *)vlibro;
    char *s = libro->titulo;
    int suma = 0, bloque = 0, i = 0;
    for (i = 0; s[i] != '\0'; i++)
    {
        bloque += (int)toupper((unsigned char)s[i]);
        if ((i + 1) % 4 == 0) { suma += bloque; bloque = 0; }
    }
    suma += bloque;
    return suma < 0 ? -suma : suma;
}

// Folding para inicial de titulo: valor ASCII de la primera letra
int folding_titulo_inicial(void *vlibro)
{
    Libro *libro = (Libro *)vlibro;
    return toupper((unsigned char)libro->titulo[0]);
}

// Folding para autor: suma bloques de 4 chars
int folding_autor(void *vlibro)
{
    Libro *libro = (Libro *)vlibro;
    char *s = libro->autor;
    int suma = 0, bloque = 0, i = 0;
    for (i = 0; s[i] != '\0'; i++)
    {
        bloque += (int)toupper((unsigned char)s[i]);
        if ((i + 1) % 4 == 0) { suma += bloque; bloque = 0; }
    }
    suma += bloque;
    return suma < 0 ? -suma : suma;
}

// Folding para inicial de autor: valor ASCII de la primera letra
int folding_autor_inicial(void *vlibro)
{
    Libro *libro = (Libro *)vlibro;
    return toupper((unsigned char)libro->autor[0]);
}

// Folding para fecha: el anio directamente
int folding_fecha(void *vlibro)
{
    Libro *libro = (Libro *)vlibro;
    return libro->fecha;
}

/* ============================================================
   FUNCIONES DE COMPARACION
   ============================================================ */

int comparar_isbn(void *a, void *b)
{
    return strcmp(((Libro *)a)->isbn, ((Libro *)b)->isbn);
}

int comparar_titulo(void *a, void *b)
{
    return strcmp(((Libro *)a)->titulo, ((Libro *)b)->titulo);
}

int comparar_titulo_inicial(void *a, void *b)
{
    char ca = toupper((unsigned char)((Libro *)a)->titulo[0]);
    char cb = toupper((unsigned char)((Libro *)b)->titulo[0]);
    return ca - cb;
}

int comparar_autor(void *a, void *b)
{
    return strcmp(((Libro *)a)->autor, ((Libro *)b)->autor);
}

int comparar_autor_inicial(void *a, void *b)
{
    char ca = toupper((unsigned char)((Libro *)a)->autor[0]);
    char cb = toupper((unsigned char)((Libro *)b)->autor[0]);
    return ca - cb;
}

int comparar_fecha(void *a, void *b)
{
    return ((Libro *)a)->fecha - ((Libro *)b)->fecha;
}

// Comparar por fecha primero, luego titulo (para rango de fechas)
int comparar_fecha_titulo(void *a, void *b)
{
    int df = ((Libro *)a)->fecha - ((Libro *)b)->fecha;
    if (df != 0) return df;
    return strcmp(((Libro *)a)->titulo, ((Libro *)b)->titulo);
}

/* ============================================================
   HELPERS: crear tabla y liberar tabla
   ============================================================ */

HashQTable *crear_tabla(int (*folding)(void *), int (*comparar)(void *, void *))
{
    HashQTable *t = malloc(sizeof(HashQTable));
    if (!t) return NULL;
    t->len   = 100; // factor de carga inicial ~50% para 50 libros
    t->cant  = 0;
    t->table = calloc(t->len, sizeof(void *));
    if (!t->table) { free(t); return NULL; }
    t->imprimir = imprimirLibro;
    t->folding  = folding;
    t->comparar = comparar;
    t->verbose  = 0;
    t->min      = 30;
    t->max      = 60;
    t->fixed    = 45; // remapar al 45% (punto medio entre 30 y 60)
    return t;
}

void liberar_tabla(HashQTable *t)
{
    if (!t) return;
    free(t->table);
    free(t);
}

/* ============================================================
   PROTOTIPOS INTERNOS
   ============================================================ */
void mostrar_menu(void);
void realizar_busqueda_isbn(HashQTable *tabla_isbn);
void realizar_busqueda_titulo(HashQTable *tabla_titulo, HashQTable *tabla_titulo_inicial);
void realizar_busqueda_autor(HashQTable *tabla_autor, HashQTable *tabla_autor_inicial);
void realizar_busqueda_fecha(HashQTable *tabla_fecha);
void eliminar_libro(HashQTable *tabla_isbn, HashQTable *tabla_titulo,
                    HashQTable *tabla_titulo_inicial, HashQTable *tabla_autor,
                    HashQTable *tabla_autor_inicial, HashQTable *tabla_fecha);
void imprimir_biblioteca(HashQTable *tabla);
void mostrar_tabla_hash(HashQTable *tabla);

// Recorre la tabla e inserta en arbol cada libro cuya inicial este en [min,max]
// comparar_arbol es la funcion de orden para el arbol resultado
static void rango_inicial_a_arbol(HashQTable *tabla, char min, char max,
                                   char (*get_inicial)(void *),
                                   int (*comparar_arbol)(void *, void *),
                                   Arbol *arbol)
{
    for (int i = 0; i < (int)tabla->len; i++)
    {
        void *entry = tabla->table[i];
        if (entry == NULL || entry == (void *)tabla) continue;
        char ini = get_inicial(entry);
        if (ini >= min && ini <= max)
            insertarArbol(arbol, entry);
    }
}

static void rango_fecha_a_arbol(HashQTable *tabla, int min, int max,
                                 int (*comparar_arbol)(void *, void *),
                                 Arbol *arbol)
{
    for (int i = 0; i < (int)tabla->len; i++)
    {
        void *entry = tabla->table[i];
        if (entry == NULL || entry == (void *)tabla) continue;
        int f = ((Libro *)entry)->fecha;
        if (f >= min && f <= max)
            insertarArbol(arbol, entry);
    }
}

static char get_inicial_titulo(void *v) { return toupper((unsigned char)((Libro *)v)->titulo[0]); }
static char get_inicial_autor(void *v)  { return toupper((unsigned char)((Libro *)v)->autor[0]); }

/* ============================================================
   MAIN
   ============================================================ */
int main(void)
{
    int i, opcion;

    Acervo acervo = obtener_libros();
    Libro *Biblioteca = acervo.libros;

    // Crear tablas
    HashQTable *tabla_isbn           = crear_tabla(folding_isbn,          comparar_isbn);
    HashQTable *tabla_titulo         = crear_tabla(folding_titulo,         comparar_titulo);
    HashQTable *tabla_titulo_inicial = crear_tabla(folding_titulo_inicial, comparar_titulo_inicial);
    HashQTable *tabla_autor          = crear_tabla(folding_autor,          comparar_autor);
    HashQTable *tabla_autor_inicial  = crear_tabla(folding_autor_inicial,  comparar_autor_inicial);
    HashQTable *tabla_fecha          = crear_tabla(folding_fecha,          comparar_fecha);

    if (!tabla_isbn || !tabla_titulo || !tabla_titulo_inicial ||
        !tabla_autor || !tabla_autor_inicial || !tabla_fecha)
    {
        printf("\nError: No se pudo crear alguna de las tablas hash\n");
        liberar_tabla(tabla_isbn);
        liberar_tabla(tabla_titulo);
        liberar_tabla(tabla_titulo_inicial);
        liberar_tabla(tabla_autor);
        liberar_tabla(tabla_autor_inicial);
        liberar_tabla(tabla_fecha);
        return 1;
    }

    // Cargar datos
    printf("\n CARGANDO DATOS DE LIBROS A LAS TABLAS HASH...\n");
    for (i = 0; i < (int)acervo.cantidad; i++)
    {
        printf(" Insertando libro %d de %d...\r", i + 1, (int)acervo.cantidad);
        fn_insertKey(tabla_isbn,           &Biblioteca[i]);
        fn_insertKey(tabla_titulo,         &Biblioteca[i]);
        fn_insertKey(tabla_titulo_inicial, &Biblioteca[i]);
        fn_insertKey(tabla_autor,          &Biblioteca[i]);
        fn_insertKey(tabla_autor_inicial,  &Biblioteca[i]);
        fn_insertKey(tabla_fecha,          &Biblioteca[i]);

    }
	
	// Verificar factor de carga y remapar si es necesario
    remap(tabla_isbn);
    remap(tabla_titulo);
    remap(tabla_titulo_inicial);
    remap(tabla_autor);
    remap(tabla_autor_inicial);
    remap(tabla_fecha);
    printf("\n DATOS CARGADOS CORRECTAMENTE.\n\n");

    imprimir_biblioteca(tabla_isbn);

    do {
        mostrar_menu();
        printf("\n INGRESE UNA OPCION: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
            case 0:
                printf("\n MOSTRANDO BIBLIOTECA:\n");
                imprimir_biblioteca(tabla_isbn);
                break;
            case 1:
                realizar_busqueda_isbn(tabla_isbn);
                break;
            case 2:
                realizar_busqueda_titulo(tabla_titulo, tabla_titulo_inicial);
                break;
            case 3:
                realizar_busqueda_autor(tabla_autor, tabla_autor_inicial);
                break;
            case 4:
                realizar_busqueda_fecha(tabla_fecha);
                break;
            case 5:
                eliminar_libro(tabla_isbn, tabla_titulo, tabla_titulo_inicial,
                               tabla_autor, tabla_autor_inicial, tabla_fecha);
                break;
            case 6:
                printf("\n SALIENDO DEL PROGRAMA...\n");
                break;
            case 7:
                mostrar_tabla_hash(tabla_isbn);
                break;
            default:
                printf("\n OPCION INVALIDA. INTENTE NUEVAMENTE.\n");
        }
    } while (opcion != 6);

    printf("\n LIBERANDO MEMORIA...\n");
    liberar_tabla(tabla_isbn);
    liberar_tabla(tabla_titulo);
    liberar_tabla(tabla_titulo_inicial);
    liberar_tabla(tabla_autor);
    liberar_tabla(tabla_autor_inicial);
    liberar_tabla(tabla_fecha);

    printf("\n FIN DE PROGRAMA\n");
    return 0;
}

/* ============================================================
   MENU
   ============================================================ */
void mostrar_menu(void)
{
    printf("\n\n ========== MENU DE BUSQUEDAS ==========\n");
    printf(" 0. MOSTRAR BIBLIOTECA\n");
    printf(" 1. BUSCAR POR ISBN\n");
    printf(" 2. BUSCAR POR TITULO\n");
    printf(" 3. BUSCAR POR AUTOR\n");
    printf(" 4. BUSCAR POR FECHA\n");
    printf(" 5. ELIMINAR LIBRO\n");
    printf(" 6. SALIR\n");
    printf(" 7. MOSTRAR TABLA HASH DE ISBN\n");
    printf(" ======================================\n");
}

/* ============================================================
   BUSQUEDAS
   ============================================================ */

void realizar_busqueda_isbn(HashQTable *tabla_isbn)
{
    char isbn[MAX_ISBN];
    printf("\n INGRESE EL ISBN DEL LIBRO: ");
    fgets(isbn, MAX_ISBN, stdin);
    if (isbn[strlen(isbn) - 1] == '\n') isbn[strlen(isbn) - 1] = '\0';

    // Libro temporal para busqueda
    Libro clave;
    strncpy(clave.isbn, isbn, MAX_ISBN);

    Libro *libro = (Libro *)fn_searchKey(tabla_isbn, &clave);
    if (libro)
    {
        printf("\n LIBRO ENCONTRADO:\n");
        printf(" %-18s | %-41s | %-25s | %-4s | %s\n", "ISBN", "TITULO", "AUTOR", "ANIO", "ESTADO");
        printf(" -----------------------------------------------------------------------------------------------\n");
        printf(" "); imprimirLibro(libro); printf("\n");
    }
    else
        printf("\n NO SE ENCONTRO NINGUN LIBRO CON ISBN '%s'.\n", isbn);
}

void realizar_busqueda_titulo(HashQTable *tabla_titulo, HashQTable *tabla_titulo_inicial)
{
    int subopcion;
    char titulo[MAX_TITULO];
    char min, max;

    printf("\n BUSQUEDA POR TITULO:\n");
    printf(" 1. BUSCAR POR TITULO COMPLETO\n");
    printf(" 2. BUSCAR POR RANGO DE INICIALES\n");
    printf(" INGRESE UNA OPCION: ");
    scanf("%d", &subopcion);
    getchar();

    switch (subopcion)
    {
        case 1:
            printf("\n INGRESE EL TITULO DEL LIBRO: ");
            fgets(titulo, MAX_TITULO, stdin);
            if (titulo[strlen(titulo) - 1] == '\n') titulo[strlen(titulo) - 1] = '\0';

            Libro clave;
            strncpy(clave.titulo, titulo, MAX_TITULO);

            Libro *libro = (Libro *)fn_searchKey(tabla_titulo, &clave);
            if (libro)
            {
                printf("\n LIBRO ENCONTRADO:\n");
                printf(" %-18s | %-41s | %-25s | %-4s | %s\n", "ISBN", "TITULO", "AUTOR", "ANIO", "ESTADO");
                printf(" -----------------------------------------------------------------------------------------------\n");
                printf(" "); imprimirLibro(libro); printf("\n");
            }
            else
                printf("\n NO SE ENCONTRO NINGUN LIBRO CON TITULO '%s'.\n", titulo);
            break;

        case 2:
            printf("\n INGRESE INICIAL MINIMA (A-Z): ");
            scanf(" %c", &min); getchar();
            min = toupper((unsigned char)min);
            printf(" INGRESE INICIAL MAXIMA (A-Z): ");
            scanf(" %c", &max); getchar();
            max = toupper((unsigned char)max);
            if (min > max) { printf("\n RANGO INVALIDO.\n"); return; }

            Arbol arbol = {NULL, 0, imprimirLibro, comparar_titulo, NULL};
            rango_inicial_a_arbol(tabla_titulo_inicial, min, max, get_inicial_titulo, comparar_titulo, &arbol);
            if (arbol.cantidad > 0)
            {
                printf("\n LIBROS ENCONTRADOS (ORDENADOS POR TITULO):\n");
                printf(" %-18s | %-41s | %-25s | %-4s | %s\n", "ISBN", "TITULO", "AUTOR", "ANIO", "ESTADO");
                printf(" -----------------------------------------------------------------------------------------------\n");
                imprimirOrden(arbol, ORDEN);
                printf("\n");
                vaciarArbol(&arbol);
            }
            else
                printf("\n NO SE ENCONTRARON LIBROS CON INICIALES ENTRE '%c' Y '%c'.\n", min, max);
            break;

        default:
            printf("\n OPCION INVALIDA.\n");
    }
}

void realizar_busqueda_autor(HashQTable *tabla_autor, HashQTable *tabla_autor_inicial)
{
    int subopcion;
    char autor[MAX_AUTOR];
    char min, max;

    printf("\n BUSQUEDA POR AUTOR:\n");
    printf(" 1. BUSCAR POR NOMBRE DE AUTOR\n");
    printf(" 2. BUSCAR POR RANGO DE INICIALES\n");
    printf(" INGRESE UNA OPCION: ");
    scanf("%d", &subopcion);
    getchar();

    switch (subopcion)
    {
        case 1:
            printf("\n INGRESE EL NOMBRE DEL AUTOR: ");
            fgets(autor, MAX_AUTOR, stdin);
            if (autor[strlen(autor) - 1] == '\n') autor[strlen(autor) - 1] = '\0';

            // La busqueda por autor puede tener multiples libros; recorremos la tabla
            // e insertamos en arbol ordenado por fecha
            Arbol arbol = {NULL, 0, imprimirLibro, comparar_fecha_titulo, NULL};
            for (int i = 0; i < (int)tabla_autor->len; i++)
            {
                void *entry = tabla_autor->table[i];
                if (entry == NULL || entry == (void *)tabla_autor) continue;
                if (strcmp(((Libro *)entry)->autor, autor) == 0)
                    insertarArbol(&arbol, entry);
            }
            if (arbol.cantidad > 0)
            {
                printf("\n LIBROS ENCONTRADOS (ORDENADOS POR FECHA):\n");
                printf(" %-18s | %-41s | %-25s | %-4s | %s\n", "ISBN", "TITULO", "AUTOR", "ANIO", "ESTADO");
                printf(" -----------------------------------------------------------------------------------------------\n");
                imprimirOrden(arbol, ORDEN);
                printf("\n");
                vaciarArbol(&arbol);
            }
            else
                printf("\n NO SE ENCONTRARON LIBROS DEL AUTOR '%s'.\n", autor);
            break;

        case 2:
            printf("\n INGRESE INICIAL MINIMA (A-Z): ");
            scanf(" %c", &min); getchar();
            min = toupper((unsigned char)min);
            printf(" INGRESE INICIAL MAXIMA (A-Z): ");
            scanf(" %c", &max); getchar();
            max = toupper((unsigned char)max);
            if (min > max) { printf("\n RANGO INVALIDO.\n"); return; }

            // Ordenado por inicial de autor (luego por autor completo)
            Arbol arbol2 = {NULL, 0, imprimirLibro, comparar_autor, NULL};
            rango_inicial_a_arbol(tabla_autor_inicial, min, max, get_inicial_autor, comparar_autor, &arbol2);
            if (arbol2.cantidad > 0)
            {
                printf("\n LIBROS ENCONTRADOS (ORDENADOS POR AUTOR):\n");
                printf(" %-18s | %-41s | %-25s | %-4s | %s\n", "ISBN", "TITULO", "AUTOR", "ANIO", "ESTADO");
                printf(" -----------------------------------------------------------------------------------------------\n");
                imprimirOrden(arbol2, ORDEN);
                printf("\n");
                vaciarArbol(&arbol2);
            }
            else
                printf("\n NO SE ENCONTRARON LIBROS CON INICIALES DE AUTOR ENTRE '%c' Y '%c'.\n", min, max);
            break;

        default:
            printf("\n OPCION INVALIDA.\n");
    }
}

void realizar_busqueda_fecha(HashQTable *tabla_fecha)
{
    int subopcion, fecha, min, max;

    printf("\n BUSQUEDA POR FECHA:\n");
    printf(" 1. BUSCAR POR ANIO ESPECIFICO\n");
    printf(" 2. BUSCAR POR RANGO DE ANIOS\n");
    printf(" INGRESE UNA OPCION: ");
    scanf("%d", &subopcion);
    getchar();

    switch (subopcion)
    {
        case 1:
            printf("\n INGRESE EL ANIO DE PUBLICACION: ");
            scanf("%d", &fecha); getchar();

            // Puede haber varios libros del mismo anio; recorremos e insertamos en arbol por titulo
            Arbol arbol = {NULL, 0, imprimirLibro, comparar_titulo, NULL};
            for (int i = 0; i < (int)tabla_fecha->len; i++)
            {
                void *entry = tabla_fecha->table[i];
                if (entry == NULL || entry == (void *)tabla_fecha) continue;
                if (((Libro *)entry)->fecha == fecha)
                    insertarArbol(&arbol, entry);
            }
            if (arbol.cantidad > 0)
            {
                printf("\n LIBROS ENCONTRADOS (PUBLICADOS EN %d):\n", fecha);
                printf(" %-18s | %-41s | %-25s | %-4s | %s\n", "ISBN", "TITULO", "AUTOR", "ANIO", "ESTADO");
                printf(" -----------------------------------------------------------------------------------------------\n");
                imprimirOrden(arbol, ORDEN);
                printf("\n");
                vaciarArbol(&arbol);
            }
            else
                printf("\n NO SE ENCONTRARON LIBROS PUBLICADOS EN %d.\n", fecha);
            break;

        case 2:
            printf("\n INGRESE ANIO MINIMO: ");
            scanf("%d", &min); getchar();
            printf(" INGRESE ANIO MAXIMO: ");
            scanf("%d", &max); getchar();
            if (min > max) { printf("\n RANGO INVALIDO.\n"); return; }

            Arbol arbol2 = {NULL, 0, imprimirLibro, comparar_fecha_titulo, NULL};
            rango_fecha_a_arbol(tabla_fecha, min, max, comparar_fecha_titulo, &arbol2);
            if (arbol2.cantidad > 0)
            {
                printf("\n LIBROS ENCONTRADOS (PUBLICADOS ENTRE %d Y %d):\n", min, max);
                printf(" %-18s | %-41s | %-25s | %-4s | %s\n", "ISBN", "TITULO", "AUTOR", "ANIO", "ESTADO");
                printf(" -----------------------------------------------------------------------------------------------\n");
                imprimirOrden(arbol2, ORDEN);
                printf("\n");
                vaciarArbol(&arbol2);
            }
            else
                printf("\n NO SE ENCONTRARON LIBROS PUBLICADOS ENTRE %d Y %d.\n", min, max);
            break;

        default:
            printf("\n OPCION INVALIDA.\n");
    }
}

/* ============================================================
   ELIMINAR LIBRO
   ============================================================ */
void eliminar_libro(HashQTable *tabla_isbn, HashQTable *tabla_titulo,
                    HashQTable *tabla_titulo_inicial, HashQTable *tabla_autor,
                    HashQTable *tabla_autor_inicial, HashQTable *tabla_fecha)
{
    char isbn[MAX_ISBN];
    printf("\n INGRESE EL ISBN DEL LIBRO A ELIMINAR: ");
    fgets(isbn, MAX_ISBN, stdin);
    if (isbn[strlen(isbn) - 1] == '\n') isbn[strlen(isbn) - 1] = '\0';

    Libro clave;
    strncpy(clave.isbn, isbn, MAX_ISBN);

    // Primero buscamos en isbn para obtener el puntero real del libro
    Libro *libro = (Libro *)fn_searchKey(tabla_isbn, &clave);
    if (!libro)
    {
        printf("\n NO SE ENCONTRO NINGUN LIBRO CON ISBN '%s'.\n", isbn);
        return;
    }

    // Eliminamos de todas las tablas usando el mismo puntero
    fn_deleteKey(tabla_isbn,           libro);
    fn_deleteKey(tabla_titulo,         libro);
    fn_deleteKey(tabla_titulo_inicial, libro);
    fn_deleteKey(tabla_autor,          libro);
    fn_deleteKey(tabla_autor_inicial,  libro);
    fn_deleteKey(tabla_fecha,          libro);

    // Remapar si factor de carga sale del rango
    remap(tabla_isbn);
    remap(tabla_titulo);
    remap(tabla_titulo_inicial);
    remap(tabla_autor);
    remap(tabla_autor_inicial);
    remap(tabla_fecha);

    printf("\n LIBRO '%s' ELIMINADO CORRECTAMENTE.\n", libro->titulo);
}

/* ============================================================
   IMPRIMIR BIBLIOTECA (recorre tabla_isbn)
   ============================================================ */
void imprimir_biblioteca(HashQTable *tabla)
{
    if (!tabla || tabla->cant == 0)
    {
        printf("\n NO HAY LIBROS PARA MOSTRAR\n");
        return;
    }
    printf("\n LISTADO DE LIBROS DISPONIBLES:\n");
    printf(" %-18s | %-41s | %-25s | %-4s | %s\n", "ISBN", "TITULO", "AUTOR", "ANIO", "ESTADO");
    printf(" -----------------------------------------------------------------------------------------------\n");
    int mostrados = 0;
    for (int i = 0; i < (int)tabla->len; i++)
    {
        void *entry = tabla->table[i];
        if (entry == NULL || entry == (void *)tabla) continue;
        printf(" "); imprimirLibro(entry); printf("\n");
        mostrados++;
        if (mostrados == (int)tabla->cant) break;
    }
    printf(" -----------------------------------------------------------------------------------------------\n");
    printf(" Total de libros: %d\n", mostrados);
}

/* ============================================================
   MOSTRAR TABLA HASH
   ============================================================ */
void mostrar_tabla_hash(HashQTable *tabla)
{
    if (!tabla) { printf("\nTABLA HASH NO EXISTE\n"); return; }
    printf("\nESTRUCTURA DE LA TABLA HASH (ISBN):\n");
    printf("INDICE | %-18s | %-41s | %-25s | %-4s | %s\n", "ISBN", "TITULO", "AUTOR", "ANIO", "ESTADO");
    printf("-----------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < (int)tabla->len; i++)
    {
        printf("%6d | ", i);
        void *entry = tabla->table[i];
        if (entry == NULL)
            printf("<VACIO>");
        else if (entry == (void *)tabla)
            printf("<ELIMINADO>");
        else
            imprimirLibro(entry);
        printf("\n");
    }
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("TAMANO REAL DE LA TABLA: %d\n", tabla->len);
    printf("ELEMENTOS ALMACENADOS: %d\n", tabla->cant);
}