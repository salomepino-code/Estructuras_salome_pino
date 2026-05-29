#include "HashQ.h"


int fn_hashQ(HashQTable hashtable,int key)
{
	return key % hashtable.len;
}

int fn_rehashQ(HashQTable hashtable,int index,int k)
{
	return (index+k*k) % hashtable.len;	
}

int fn_insertKey(HashQTable *hashtable,void *data)
{
	int index,n_index,k=0,key;
	key = hashtable->folding(data);
	index = fn_hashQ(*hashtable,key);
	
	if( hashtable->table[index] == NULL || hashtable->table[index]==hashtable )
	{
		hashtable->table[index] = data;
		hashtable->cant++;
		if(hashtable->verbose)printf("\n K: %d",k);
		return 1;
	}
	else
	{
		k = 1;
		n_index = fn_rehashQ(*hashtable,index,k);
		
		while(hashtable->table[n_index] != NULL && hashtable->table[n_index] != hashtable)
		{			
			k += 1;
			n_index = fn_rehashQ(*hashtable,index,k);
			
		}		
		hashtable->table[n_index] = data;
		hashtable->cant++;
		if(hashtable->verbose)printf("\n K: %d",k);
		return 1;		
	}	
}


void* fn_searchKey(HashQTable *hashtable,void *data)
{	
	int index,n_index,k=0,key;
	key = hashtable->folding(data);
	index = fn_hashQ(*hashtable,key);
	
	if(hashtable->table[index]==NULL)
		return NULL;
	void *dataTable = hashtable->table[index];
	
	if( hashtable!=dataTable && hashtable->comparar(dataTable,data) == 0 )
	{	
		if(hashtable->verbose)printf("\n K: %d",k);
		return dataTable;	
	}
	
	else
	{
		k = 1;
		n_index = fn_rehashQ(*hashtable,index,k);
		dataTable = hashtable->table[n_index];
		
		while(dataTable != NULL )
		{
			if( hashtable!=dataTable &&  hashtable->comparar(dataTable,data) == 0)
			{
				if(hashtable->verbose)printf("\n K: %d",k);
				return dataTable;	
			}			
			k += 1;
			n_index = fn_rehashQ(*hashtable,index,k);
			dataTable = hashtable->table[n_index];		
		}
		if(hashtable->verbose)printf("\n K: %d",k);
		return NULL;
	}
}


void* fn_deleteKey(HashQTable *hashtable,void *data)
{	
	int index,n_index,k=0,key;
	key = hashtable->folding(data);
	index = fn_hashQ(*hashtable,key);
	
	if(hashtable->table[index]==NULL)
		return NULL;
	void *dataTable = hashtable->table[index];
	
	if( hashtable!=dataTable && hashtable->comparar(dataTable,data) == 0 )
	{	
		if(hashtable->verbose)printf("\n K: %d",k);			
		hashtable->table[index] = hashtable;
		hashtable->cant--;
		return dataTable;
	}
	
	else
	{
		k = 1;
		n_index = fn_rehashQ(*hashtable,index,k);
		dataTable = hashtable->table[n_index];
		
		while(dataTable != NULL )
		{			
			if(dataTable != hashtable && hashtable->comparar(dataTable,data) == 0)
			{
				if(hashtable->verbose)printf("\n K: %d",k);
				hashtable->table[n_index] = hashtable;
				hashtable->cant--;
				return dataTable;	
			}			
			k += 1;
			n_index = fn_rehashQ(*hashtable,index,k);
			dataTable = hashtable->table[n_index];		
		}
		return NULL;
	}
}



void remap(HashQTable *hashtable)
{
	float factor = hashtable->cant *100 / hashtable->len;
	if( factor > hashtable->max || factor < hashtable->min)
	{		
		int inserted = 0;
		void *dataTable;
		void **oldTable = hashtable->table;
		int oldLen = hashtable->len;
		int oldCant = hashtable->cant;
		hashtable->len = hashtable->cant * 100 / hashtable->fixed;
		hashtable->cant = 0;				
		hashtable->table = calloc( hashtable->len  ,sizeof(void*));
		for(int i = 0; i < oldLen ; i++)
		{
			dataTable= oldTable[i];
			if( dataTable!=hashtable && dataTable!=NULL)
			{
				fn_insertKey(hashtable,oldTable[i]);
				inserted++;
			}
			if( inserted == oldCant)
				break;			
		}		
		free(oldTable);
	}
}