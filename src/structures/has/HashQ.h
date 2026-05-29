#ifndef HASHQ_H
#define HASHQ_H

#include <stdio.h>
#include <stdlib.h>

typedef void (*fn_imprimir)(void*);
typedef int (*fn_folding)(void*);
typedef int (*fn_comparar)(void*,void*);

typedef struct
{
	void **table;
	unsigned int len;
	unsigned int cant;
	fn_imprimir imprimir;
	fn_folding folding;
	fn_comparar comparar;
	int verbose;
	int min,max,fixed;
}HashQTable;

int fn_hashQ(HashQTable hashtable,int key);
int fn_rehashQ(HashQTable hashtable,int index,int k);
int fn_insertKey(HashQTable *hashtable,void *data);
void* fn_searchKey(HashQTable *hashtable,void *data);
void* fn_deleteKey(HashQTable *hashtable,void *data);
void remap(HashQTable *hashtable);



#endif