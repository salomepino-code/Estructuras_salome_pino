#include "expresion.h"

double evaluar(Arbol arbol)
{
	NodoA **arrOrigin = calloc(arbol.cantidad,sizeof(NodoA*));
	if(!arrOrigin)
	{
		printf("\n NO SE PUDO ASIGNAR EL ARREGLO DE NODOS");
		exit(1);
	}
	int cantidad = 0;
	extraerNodos(arbol.raiz,arrOrigin,&cantidad);	
	asignarMemoria(arrOrigin,cantidad,arbol.comparar);
	capturarValores(arrOrigin,cantidad);
		
	//AQUI LLAMAR A LA FUNCION QUE CALCULA EL RESULTADO
	double resultado = calcular(arbol.raiz);
	printf("\n RESULTADO = %lf\n", resultado);	
		
	//LIBERAR MEMORIA RESERVADA	
	liberarMemoriaValores(arrOrigin,cantidad);	
	free(arrOrigin);
	return 0;
}

void extraerNodos(NodoA *raiz,NodoA **nodos,int *i)
{	
	if(!raiz)
		return;
	extraerNodos(raiz->izq,nodos,i);
	nodos[ (*i) ] = raiz;
	(*i)++;
	extraerNodos(raiz->dch,nodos,i);	
}

void asignarMemoria(NodoA **original,int cantidad,int (*comparar)(void*,void*))
{
	//CREAR ARREGLO AUXILIAR
	int *indices = (int*)calloc(cantidad,sizeof(int));	
	if(!indices)
	{
		printf("\n NO SE PUDO ASIGNAR EL ARREGLO DE INDICES");
		exit(1);
	}	
	//ARREGLO AUXILIAR PARA DETECTAR DUPLICADOS
	//EN EL ARREGLO SE ASIGNAN EL INDICE DEL LA PRIMERA
	//COINCIDENCIA
	for(int i = 0; i < cantidad; i++)
		indices[i] = -1;
	for(int i = 0 ; i < cantidad; i++)
	{	
		//OMITE SI YA SE REGISTRO
		if( indices[i] != -1)
			continue;			
		//OMITE SI ES UN OPERADOR
		if(  precedencia(original[i]->dato) != OPERANDO)
			continue;	
		
		for(int j = i; j < cantidad; j++)
		{
			if( comparar(original[i]->dato,original[j]->dato)==0)				
				indices[j] = i;
		}
		double **ptr = calloc(1,sizeof(double*));		
		for(int j = 0; j < cantidad; j++)
		{
			if(indices[j] == i)
				((Variable*)(original[j]->dato))->v  = ptr;
		}	
		
	}
	free(indices);
}


void capturarValores(NodoA **original,int cantidad)
{
	printf("\n\n CAPTURAR VALORES \n");
	for(int i = 0;i<cantidad;i++)
	{		
		if( precedencia(original[i]->dato) != OPERANDO )
			continue;
		if(((Variable*)original[i]->dato)->v != NULL  && *((Variable*)original[i]->dato)->v == NULL )
		{
			*((Variable*)original[i]->dato)->v = calloc(1,sizeof(double));
			printf("\n Captura variable %c: ", ((Variable*)original[i]->dato)->c) ;
			inputDouble("",*((Variable*)original[i]->dato)->v);
		}			
	}	
}


void liberarMemoriaValores(NodoA **original,int cantidad)
{
	//CREAR ARREGLO AUXILIAR
	int *indices = (int*)calloc(cantidad,sizeof(int));	
	if(!indices)
	{
		printf("\n NO SE PUDO ASIGNAR EL ARREGLO DE INDICES");
		exit(1);
	}	
	//ARREGLO AUXILIAR PARA DETECTAR DUPLICADOS
	//EN EL ARREGLO SE ASIGNAN EL INDICE DEL LA PRIMERA
	//COINCIDENCIA
	for(int i = 0; i < cantidad; i++)
		indices[i] = -1;
	
	for(int i = 0;i<cantidad;i++)
	{		
		if( precedencia(original[i]->dato) != OPERANDO )
			continue;
		if( ((Variable*)original[i]->dato)->v != NULL)
		{
			//REGISTRAR DUPLICADOS
			for(int j = i; j < cantidad; j++)
			{
				if( ((Variable*)original[i]->dato)->v == ((Variable*)original[j]->dato)->v)				
					indices[j] = i;
			}	
			//LIBERAR DATO FLOTANTE double
			free( *((Variable*)original[i]->dato)->v );
			//LIBERAR APUNTADOR double*
			free( ((Variable*)original[i]->dato)->v  );
			//QUITAR DE DUPLICADOS
			for(int j = 0; j < cantidad; j++)
			{
				if( indices[j] == i )
					((Variable*)original[j]->dato)->v = NULL;
			}	
		}				
	}	
	free(indices);
}



