#include <stdio.h>
#include <stdlib.h>

#include <iostring.h>
#include <arbol.h>


int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);

int altura(NodoA*);
int igualesEstructura(NodoA*,NodoA*);
int igualesDatos(NodoA*,NodoA*);
void compararArboles(Arbol,Arbol);

NodoA* eliminarNodo(NodoA*,int);
void eliminarDato(Arbol*,int);

void equilibrar(Arbol*);
void extraerDatos(NodoA *raiz,void **datos,int *i);
void generarArbol(Arbol *arbol,void **datos,int longitud);
void eliminararArbol(Arbol*);
void prof(NodoA *raiz, int *altura, int nivel);

int main(void)
{
	Arbol A = {NULL,0,imprimirEntero,compararEntero,free};
	Arbol B = {NULL,0,imprimirEntero,compararEntero,free};

	int op, dato;
	
	insertarArbol(&A,crearEntero(8));
	insertarArbol(&A,crearEntero(7));
	insertarArbol(&A,crearEntero(10));
	insertarArbol(&A,crearEntero(9));
	insertarArbol(&A,crearEntero(11));
	insertarArbol(&A,crearEntero(6));
	insertarArbol(&A,crearEntero(4));
	insertarArbol(&A,crearEntero(1));
	insertarArbol(&A,crearEntero(5));
	
	insertarArbol(&B,crearEntero(8));
	insertarArbol(&B,crearEntero(7));
	insertarArbol(&B,crearEntero(10));
	insertarArbol(&B,crearEntero(9));
	insertarArbol(&B,crearEntero(11));
	insertarArbol(&B,crearEntero(6));
	insertarArbol(&B,crearEntero(4));
	insertarArbol(&B,crearEntero(1));
	insertarArbol(&B,crearEntero(5));
	
	do{
		printf("\n\n--- MENU ---\n");
		printf("1. Insertar en Arbol A\n");
		printf("2. Insertar en Arbol B\n");
		printf("3. Comparar Arboles\n");
		printf("4. Eliminar en Arbol A\n");
		printf("5. Eliminar en Arbol B\n");
		printf("6. Profundidades\n");
		printf("7. Equilibrar Arboles\n");
		printf("8. Mostrar Arboles\n");
		printf("9. Salir\n");
		printf("Opcion: ");
		scanf("%d",&op);
	
		switch(op)
		{
			case 1:
				printf("Dato: ");
				scanf("%d",&dato);
				insertarArbol(&A,crearEntero(dato));
			break;

			case 2:
				printf("Dato: ");
				scanf("%d",&dato);
				insertarArbol(&B,crearEntero(dato));
			break;

			case 3:
				compararArboles(A,B);
			break;

			case 4:
				printf("Dato a eliminar: ");
				scanf("%d",&dato);
				eliminarDato(&A,dato);
			break;

			case 5:
				printf("Dato a eliminar: ");
				scanf("%d",&dato);
				eliminarDato(&B,dato);
			break;

			case 6:
				printf("\nAltura A: %d",altura(A.raiz));
				printf("\nAltura B: %d",altura(B.raiz));
			break;

			case 7:
				equilibrar(&A);
				equilibrar(&B);
				printf("\nArboles equilibrados");
			break;

			case 8:
				printf("\nARBOL A:\n");
				imprimirArbol(A);
				printf("\n\nARBOL B:\n");
				imprimirArbol(B);
			break;

		}

	}while(op != 9);

	eliminarArbol(&A);
	eliminarArbol(&B);

	printf("\nFIN DEL PROGRAMA\n");

	return 0;
}


int* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}

int compararEntero(void*a,void*b)
{
	int *aa = a,*bb=b;
	if(*aa==*bb)return 0;
	else if(*aa<*bb)return -1;
	else return 1;
}

void imprimirEntero(void *a)
{
	printf("%d",*(int*)a);
}

// ALTURA 

void prof(NodoA *raiz, int *altura, int nivel )
{
	if(!raiz){
		if(nivel>*altura)
			*altura = nivel;
		return;
	}
		prof(raiz->izq, altura, nivel + 1);
		prof(raiz->dch, altura, nivel + 1);
}

int altura(NodoA *raiz)
{
	int altura = 0;
	prof(raiz, &altura, 0);
	return altura;
}

// COMPARAR 

int igualesEstructura(NodoA *a, NodoA *b)
{
	if(!a && !b) return 1;
	if(!a || !b) return 0;

	return igualesEstructura(a->izq,b->izq) &&
		   igualesEstructura(a->dch,b->dch);
}

int igualesDatos(NodoA *a, NodoA *b)
{
	void **datosA = malloc(sizeof(void*) * 1000);
    void **datosB = malloc(sizeof(void*) * 1000);
    int iA = 0, iB = 0, resultado = 1;
    int i;

    extraerDatos(a, datosA, &iA);
    extraerDatos(b, datosB, &iB);

    if(iA != iB)
        resultado = 0;
    else
        for(i = 0; i < iA; i++)
            if(*(int*)datosA[i] != *(int*)datosB[i])
            {
                resultado = 0;
                break;
            }

    free(datosA);
    free(datosB);
    return resultado;
}

void compararArboles(Arbol A, Arbol B)
{
	if(A.cantidad != B.cantidad)
    {
        printf("\nSon DIFERENTES");
        return;
    }
	
	int datos = igualesDatos(A.raiz,B.raiz);
	int estructura = igualesEstructura(A.raiz,B.raiz);

	if(datos && estructura)
		printf("\nSon IGUALES en datos y estructura");
	else if(datos)
		printf("\nSolo son iguales en DATOS");
	else
		printf("\nSon DIFERENTES");
}

// ELIMINAR 

NodoA* eliminarNodo(NodoA *raiz, int dato)
{
	if(!raiz) return NULL;

	if(dato < *(int*)raiz->dato)
		raiz->izq = eliminarNodo(raiz->izq,dato);
	else if(dato > *(int*)raiz->dato)
		raiz->dch = eliminarNodo(raiz->dch,dato);
	else
	{
		if(!raiz->izq && !raiz->dch)
		{
			free(raiz->dato);
			free(raiz);
			return NULL;
		}

		if(!raiz->izq)
		{
			NodoA *tmp = raiz->dch;
			free(raiz->dato);
			free(raiz);
			return tmp;
		}

		if(!raiz->dch)
		{
			NodoA *tmp = raiz->izq;
			free(raiz->dato);
			free(raiz);
			return tmp;
		}

		NodoA *min = raiz->dch;
		while(min->izq)
			min = min->izq;
		
		int valMin = *(int*)min->dato;
		*(int*)raiz->dato = valMin;
		raiz->dch = eliminarNodo(raiz->dch, valMin);
	}

	return raiz;
}

void eliminarDato(Arbol *arbol,int dato)
{
	arbol->raiz = eliminarNodo(arbol->raiz,dato);
	arbol->cantidad--;
}

//================ EQUILIBRAR =================

void extraerDatos(NodoA *raiz,void **datos,int *i)
{
	if(!raiz)
		return;
	extraerDatos(raiz->izq, datos, i);
	datos*[i] = raiz->dato;
	*(i)++;
	extraerDatos(raiz->izq, datos, i);
}

void generarArbol(Arbol *arbol,void **datos,int longitud)
{
	if(longitud <= 0)
		return;

	int mitad = longitud/2;

	insertarArbol(arbol,datos[mitad]);

	generarArbol(arbol,datos,mitad);
	generarArbol(arbol,datos+mitad+1,longitud-1-mitad);
}

void equilibrar(Arbol *arbol)
{
    if(!arbol->raiz)
        return;

    void **datos = (void**) calloc(arbol->cantidad,sizeof(void*));
    int i = 0;

    extraerDatos(arbol->raiz,datos,&i);

    vaciarArbol(arbol);  

    generarArbol(arbol,datos,i);

    free(datos);
}