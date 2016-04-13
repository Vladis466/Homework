#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"

struct hashLink {
   void* key; /*the key is what you use to look up a hashLink*/
   void* value; /*the value stored with the hashLink, a pointer to int in the case of concordance*/
   struct hashLink * next; /*notice how these are like linked list nodes*/
};

typedef struct hashLink hashLink;

struct hashMap {
    hashLink ** table; /*array of pointers to hashLinks*/
    int tableSize; /*number of buckets in the table*/
    int count; /*number of hashLinks in the table*/
};
typedef struct hashMap hashMap;


/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 */
void _freeMap (struct hashMap * ht)
{  
	int b1, counter, b2;
	struct hashLink *bucket;

	for (b1 = 0; b1 < ht->tableSize; b1++)	// iterate through each index in the table
	{
		if (ht->table[b1] != 0)				// if the index isnt empty
		{
			bucket = ht->table[b1];			// jump to the first bucket in that index
			counter = 1;
			while (bucket->next != 0)		// If the next bucket isn't empty.
			{
				bucket = bucket->next;		//Jump to that bucket & increment the count.
				counter++;
			}

			bucket = ht->table[b1];

			while (counter > 0)		// while there is a value in that index, go in and delete every bucket.
			{
				bucket = ht->table[b1];

				for (b2 = 0; b2 < counter - 1; b2++) // -1 because we already start at #1
				{
					bucket = bucket->next;
				}
				free(bucket->key);
				free(bucket->value);
				free(bucket);
				bucket = 0;
				counter--;					//repeat this process for each bucket in the current index.
			}
		}
	}
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/* 
Resizes the hash table to be the size newTableSize 
*/
void _setTableSize(struct hashMap * ht, int newTableSize, comparator keyCompare, hashFuncPtr hashFunc)

{	
	int i;
	struct hashMap *hn = createMap(newTableSize);
	struct hashLink *copy;

	for (i = 0; i < ht->tableSize; i++)
	{
		copy = ht->table[i];
		while (copy != 0)
		{
			insertMap(hn, copy->key, copy->value, keyCompare, hashFunc);
			copy = copy->next;
		}
	}
	ht->table = hn->table;			// copy everything over to our primary table.
	ht->tableSize = hn->tableSize;
	ht->count = hn->count;
}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".
 
 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.
 
 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, void* k, void* v, comparator keyCompare, hashFuncPtr hashFunc)
{  
	/*write this*/
	int index = hashFunc(k) % capacity(ht);								//Pass in the key k (word turned into a number already), and localize its position.
	struct hashLink *newHash = malloc(sizeof(struct hashLink));
	newHash->key = k;
	newHash->value = (int *)v;
	newHash->next = NULL;

	if (tableLoad(ht) > LOAD_FACTOR_THRESHOLD){
		_setTableSize(ht, 2 * ht->tableSize, keyCompare, hashFunc);		//if adding another hashlink makes our table too big, resize
	}

	if (ht->table[index] == 0){
		ht->table[index] = newHash;										//set the value of the new index if it doesn't already exist.
		ht->count++;
		return;
	}
	//If our index already exists in the table.
	struct hashLink *copy = ht->table[index];
	while (copy->next != 0)
	{
		if (keyCompare(k, copy->key) == 0)
		{
			copy->value = v;					//If we find the key, override the value
			free(newHash);
		}
		copy = copy->next;
	}
	copy->next = newHash;
	ht->count++;								//Have to increase the count because we added a new Hashlink.
}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.
 
 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.
 
 if the supplied key is not in the hashtable return NULL.
 */
void* atMap(struct hashMap * ht, void* k, comparator keyCompare, hashFuncPtr hashFunc)
{
	/*write this*/
	int index = hashFunc(k) % capacity(ht);		//Pass in the key k (word turned into a number already), and localize its position.
	struct hashLink *copy = ht->table[index];

	if (copy == 0)
		return NULL;
	while (keyCompare(k, copy->key) != 0)		// While the key values arent equal
	{		
		if (copy->next == 0)					//If next bucket is empty, value doesn't exist.
		{
			return NULL;
		}
		copy = copy->next;						//On to the next bucket
	}
	return copy->value;
}

/*
 a simple yes/no if the key is in the hashtable. 
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, void* k, comparator keyCompare, hashFuncPtr hashFunc)
{  
	/*write this*/
	int index = hashFunc(k) % capacity(ht);
	if (ht->table[index] == 0){
		return 0;						// index doesn't exist therefore key doesn't exist there.
	}
	struct hashLink *copy = ht->table[index];
	
	while (keyCompare(k, copy->key) != 0)		// While the key values arent equal
	{
		if (copy->next == 0)					//If next bucket is empty, value doesn't exist.
		{
			return 0;
		}
		copy = copy->next;						//On to the next bucket
	}
	return 1;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */


//DIS SHIT WONT WORK>
void removeKey(struct hashMap * ht, void* k, comparator keyCompare, hashFuncPtr hashFunc)
{
	/*write this*/
	/*
	int i = 0;
	int count = 0;
	int index = hashFunc(k) % capacity(ht);		//Pass in the key k (word turned into a number already), and localize its position.
	struct hashLink *copy;
	struct hashLink *copy2;
	copy = ht->table[index];

	if (copy == 0){
		printf("Key could not be found. \n");
		return;
	}

	copy2 = ht->table[index]->next;

	while (keyCompare(k, copy->key) != 0)		// While the key values arent equal
	{
		count++;

		if (copy->next == 0)					//If next bucket is empty, value doesn't exist.
		{
			printf("Key could not be found. \n");
			return;
		}
		copy = copy->next;						//On to the next bucket
		copy2 = copy2->next;					//the bucket in front of copy
	}

	copy = ht->table[index];
	copy2 = ht->table[index]->next;

	while (i < count -1){						//count will always be at least 1 if found because the first link has no key. Its an index.
		copy = copy->next;
		copy2 = copy2->next;
		i++;
	}
	if (copy->next != 0){
		//copy->key = copy->next->key;
		//copy->value = copy->next->value;
		copy->next = copy->next->next;
	}

	free(copy->next->key);
	free(copy->next->value);
	free(copy->next);
	*/
	int bucket = hashFunc(k) % capacity(ht);
	struct hashLink *Remover = ht->table[bucket];
	struct hashLink *temp;
	while (Remover != 0){
	if (keyCompare(Remover->key, k) == 0){
	ht->count--;
	if (Remover->next != 0){
	Remover->key = Remover->next->key;
	Remover->value = Remover->next->value;
	Remover->next = Remover->next->next;
	return;
	}
	free(ht->table[bucket]);
	ht->table[bucket] = 0;
	return;
	}
	Remover = Remover->next;
	}
	printf("Key not in hash map.\n");
	

}

/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{  
	/*write this*/
	return ht->count;
	
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{  
	/*write this*/
	return ht->tableSize;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{  
	/*write this*/
	int i = 0;
	int count = 0;
	for (i = 0; i < ht->tableSize; i++){
		if (ht->table[i] = 0){
			count++;
		}
	}
	return count;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)
 
 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{  
	/*write this*/
		
	/* 
	int load;
	int i = 0;
	int count = 0;
	hashLink *bucketCount;

	for (i = 0; i < ht->tableSize; i++)
	{
		if (ht->table[i] != 0)
		{
			bucketCount = ht->table[i];
			while (bucketCount != 0)							-------------->waste of time, forgot about ht->count...
			{
				count++;
				bucketCount = bucketCount->next;
			}
			
		}
	}

	load = count / ht->tableSize;*/
	return (float)ht->count / (float)ht->tableSize;;
}

/* print the hashMap */
 void printMap (struct hashMap * ht, keyPrinter kp, valPrinter vp)
{
        int i;
        struct hashLink *temp;
        for(i = 0;i < capacity(ht); i++){
                temp = ht->table[i];
                if(temp != 0) {
                        printf("\nBucket Index %d -> ", i);
                }
                while(temp != 0){
                        printf("Key:");
                        (*kp)(temp->key);
                        printf("| Value: ");
                        (*vp)(temp->value);
                        printf(" -> ");
                        temp=temp->next;
                }
        }
}

/* print the keys/values ..in linear form, no buckets */
 void printKeyValues (struct hashMap * ht, keyPrinter kp, valPrinter vp)
{
        int i;
        struct hashLink *temp;
        for(i = 0;i < capacity(ht); i++){
                temp = ht->table[i];
                while(temp != 0){
                        (*kp)(temp->key);
                        printf(":");
                        (*vp)(temp->value);
                        printf("\n");
                        temp=temp->next;
                }
        }
}




/* Iterator Interface */

struct mapItr {
  int count;
  struct hashLink *current;
  struct hashMap *map;
};


struct mapItr *createMapIterator(struct hashMap *ht)
{
  struct mapItr *myItr = malloc(sizeof(struct mapItr)); /* malloc_5 */
  initMapIterator(ht, myItr);
  return myItr;
}

void initMapIterator(struct hashMap *ht, struct mapItr *itr)
{
  itr->count = 0;
  itr->current = ht->table[itr->count];
  itr->map = ht;
}

int  hasNextMap(struct mapItr *itr)
{

  /* skip all the empty buckets */

  while(itr->map->table[itr->count] == 0)
    {
       itr->count++;
       itr->current = itr->map->table[itr->count];
    }

  if (itr->count >= itr->map->tableSize)
    return 0;


  return 1;

}

void*  nextMap(struct mapItr *itr)
{
  void* key;
  key = itr->current->key;

  /* set up for subsequent call to has Next */
  itr->current = itr->current->next;
  if(itr->current == 0) /* at end of the list*/
    {
   itr->count++; /*move on to the next bucket */
   itr->current = itr->map->table[itr->count];
}
  return(key);
}

void removeMap(struct mapItr *itr)
{
  printf("Not yet implemented \n");
  /* Actually only a convenience since I can iterate through, get keys, and then call removeKey */
  /* This is, in fact, how I wouldimplement it here...I would simply get the last returned key and call remove Key */
  /* A slighlty more efficient solution would include double links and allow a remove iwthout calling removeKey...but it's not worth the effort here! */

}
