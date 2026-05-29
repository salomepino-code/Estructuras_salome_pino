#include "heap.h"



Heap crearHeap(unsigned char tipo,fn_comparar comparar,fn_imprimir imprimir)
{
	Heap heap = {tipo,0,NULL,NULL,comparar,imprimir};
	return heap;
}

void insertarHeap( Heap *heap,void *dato)
{
	void **aux = NULL;
	if(!heap->cantidad)
		heap->datos = calloc(1,sizeof(void*));
	else
	{
		while(!aux)
			aux = realloc(heap->datos, (heap->cantidad+1) * sizeof(void*) );
		heap->datos = aux;
	}	
	heap->datos[heap->cantidad++] = dato;
	//HEAPIFY
	heapify(heap);
}


void* eliminarHeap(Heap *heap)
{
	void *dato = NULL;
	if(!heap->cantidad)
		return dato;
	dato = heap->datos[0];
	if(heap->cantidad == 1)		
	{
		free(heap->datos);
		heap->datos = NULL;
		heap->cantidad--;
		return dato;
	}
	heap->datos[0] = heap->datos[heap->cantidad-1];
	void **aux = NULL;
	while(!aux)
		aux = realloc(heap->datos, (heap->cantidad-1) * sizeof(void*) );
	heap->datos = aux;
	heap->cantidad--;
	//HEAPIFY
	heapify(heap);
	return dato;	
}

void imprimirHeap( Heap heap)
{
	printf("\n HEAP: \n");
	if(heap.cantidad)
	{
		for( int i = 0; i < heap.cantidad; i++)
		{
			printf(" [%d] ",i);
			heap.imprimir( heap.datos[i] );
			printf("\n");
		}
		
	}
	else		
		printf("VACIO");		
}




void heapify_min( Heap *heap,int padre)
{
	if( padre < 0 || padre > (heap->cantidad/2-1) )
		return;
	int min = padre;
	int izq = 2*padre+1;
	int dch = 2*padre+2;
	switch(heap->tipo)
	{
		case HEAP_MIN:			
			if( heap->comparar( heap->datos[min] , heap->datos[izq] ) > 0 )
				min = izq;
			if( dch < heap->cantidad && heap->comparar( heap->datos[min] , heap->datos[dch] ) > 0 )
				min = dch;
			break;			
		case HEAP_MAX:			
			if( heap->comparar( heap->datos[izq] , heap->datos[min] ) > 0 )
				min = izq;
			if( dch < heap->cantidad && heap->comparar( heap->datos[dch] , heap->datos[min] ) > 0 )
				min = dch;
			break;
	}
	if( min!=padre)
	{
		void *dato = heap->datos[padre];
		heap->datos[padre] = heap->datos[min];
		heap->datos[min] = dato;
		heapify_min(heap,min);
	}
	heapify_min(heap,padre-1);
	
	
}


void heapify(Heap *heap)
{
	int indice = heap->cantidad/2-1;
	heapify_min(heap,indice);

}