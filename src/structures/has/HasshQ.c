int fn_hashQ(HashQTable hashtable, int key)
{
	return key % HashQTable.len;
}
int fn_reHashQ(HashQTable hashtable, int index, int k)
{
	return (index+k*k) % HashQTable.len;
}

int fn_insertKey(HashQTable *hashtable, void *data)
{
	int k, key, index,	
	
	key = hashtable->folding(data);
	index = fn_hashQ(hashtable, key);
	
	if(hashtable->table[index] == NULL){
		hashtable->table[index] = data;
		hashtable->cantidad++;
	}
	else {
		
		k = 1;
		n_index = fn_reHashQ(hashtable, index, k);
			
		while (hashtable->table[n_index] != NULL){
			k += 1;
			n_index = fn_reHashQ(hashtable, index, k);
			
		}
		hashtable->table[n_index] = data;
		hashtable->cant++;
		return 1;
	}
	
}
void* fn_searchtKey(HashQTable * hashtable, voiid *data)
{
	if 
	
	else 
}
