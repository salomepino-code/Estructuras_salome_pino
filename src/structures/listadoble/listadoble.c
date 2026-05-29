#include "listadoble.h"

void insertarFinalD(ListaD *lista,void *dato)
{
	NodoD *nuevo = crearNodoD(dato);
	//LISTA VACIA
	if(!lista->inicio)
	{
		lista->inicio = lista->fin = nuevo;
	}
	//LISTA NO VACIA
	else
	{
		lista->fin->sig = nuevo;
		nuevo->ant = lista->fin;
		lista->fin = nuevo;
	}
	lista->cant++;
}

void imprimirListaDIF(ListaD lista)
{
	printf("\n [%d] LISTA:",lista.cant);
	if(!lista.inicio)
	{
		printf("VACIA");
		return;
	}
	for(NodoD *aux = lista.inicio; aux!=NULL;  aux=aux->sig )
	{
		printf("\n");
		lista.imprimir( aux->dato);
	}	
}

void imprimirListaDFI(ListaD lista)
{
	printf("\n [%d] LISTA:",lista.cant);
	if(!lista.inicio)
	{
		printf("VACIA");
		return;
	}
	for(NodoD *aux = lista.fin; aux!=NULL;  aux=aux->ant )
	{
		printf("\n");
		lista.imprimir( aux->dato);
	}
	
}



void borrarInicioD(ListaD *lista)
{
	NodoD *aux;
	if(!lista->inicio)
		return;	
	aux = lista->inicio;
	//UNICO NODO
	if( lista->inicio == lista->fin)
	{
		lista->inicio = lista->fin = NULL;
	}	
	//MINIMO 2
	else
	{
		lista->inicio = aux->sig;
		lista->inicio->ant = NULL;
		
	}
	if(lista->liberar)
		lista->liberar( aux->dato);
	free(aux);	
	lista->cant--;	
}

void borrarListaD(ListaD *lista)
{
	while(lista->inicio)
	{
		borrarInicioD(lista);
	}	
}

ListaD inicializarListaD(void)
{
    ListaD nueva;
    nueva.inicio = NULL;
    nueva.fin = NULL;
    nueva.cant = 0;
    nueva.imprimir = NULL;
    nueva.comparar = NULL;
    nueva.liberar = NULL;
    return nueva;
}

NodoD* buscarDatoD(ListaD lista, void *dato)
{
    for(NodoD *aux = lista.inicio; aux != NULL; aux = aux->sig)
    {
        if(lista.comparar(aux->dato, dato) == 0)
            return aux;
    }
    return NULL;
}

void insertarInicioD(ListaD *lista, void *dato)
{
    NodoD *nuevo = crearNodoD(dato);
    if(!lista->inicio)
    {
        lista->inicio = lista->fin = nuevo;
    }
    else
    {
        nuevo->sig = lista->inicio;
        lista->inicio->ant = nuevo;
        lista->inicio = nuevo;
    }
    lista->cant++;
}

void insertEnOrdenD(ListaD *lista, void *dato)
{
    // Si está vacía o va al inicio
    if(!lista->inicio || lista->comparar(dato, lista->inicio->dato) <= 0)
    {
        insertarInicioD(lista, dato);
        return;
    }

    NodoD *aux = lista->inicio;
    while(aux->sig && lista->comparar(dato, aux->sig->dato) > 0)
        aux = aux->sig;

    // Va al final
    if(!aux->sig)
    {
        insertarFinalD(lista, dato);
        return;
    }

    // Va en medio
    NodoD *nuevo = crearNodoD(dato);
    nuevo->sig = aux->sig;
    nuevo->ant = aux;
    aux->sig->ant = nuevo;
    aux->sig = nuevo;
    lista->cant++;
}

void borrarDatoD(ListaD *lista, void *dato)
{
    NodoD *encontrado = buscarDatoD(*lista, dato);
    if(!encontrado)
    {
        printf("\nDato no encontrado");
        return;
    }

    // Es el único nodo
    if(lista->inicio == lista->fin)
    {
        lista->inicio = lista->fin = NULL;
    }
    // Es el inicio
    else if(encontrado == lista->inicio)
    {
        lista->inicio = encontrado->sig;
        lista->inicio->ant = NULL;
    }
    // Es el fin
    else if(encontrado == lista->fin)
    {
        lista->fin = encontrado->ant;
        lista->fin->sig = NULL;
    }
    // Es un nodo del medio
    else
    {
        encontrado->ant->sig = encontrado->sig;
        encontrado->sig->ant = encontrado->ant;
    }

    if(lista->liberar)
        lista->liberar(encontrado->dato);
    free(encontrado);
    lista->cant--;
}

void reordenarD(ListaD *lista, int (*comparar)(void*, void*))
{
    // Guarda el comparador original y asigna el nuevo
    lista->comparar = comparar;

    // Insertion sort sobre la lista doble
    if(!lista->inicio) return;

    NodoD *i = lista->inicio->sig;
    while(i)
    {
        void *datoActual = i->dato;
        NodoD *j = i->ant;

        while(j && lista->comparar(j->dato, datoActual) > 0)
        {
            j->sig->dato = j->dato;
            j = j->ant;
        }

        if(!j)
            lista->inicio->dato = datoActual;
        else
            j->sig->dato = datoActual;

        i = i->sig;
    }
}





