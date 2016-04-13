#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "cirListDeque.h"

/* Double Link Struture */
struct DLink {
	TYPE value;/* value of the link */
	struct DLink * next;/* pointer to the next link */
	struct DLink * prev;/* pointer to the previous link */
};

# define TYPE_SENTINEL_VALUE DBL_MAX 


/* ************************************************************************
 Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
 ************************************************************************ */

struct cirListDeque {
	int size;/* number of links in the deque */
	struct DLink *Sentinel;	/* pointer to the sentinel */
};
/* internal functions prototypes */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);



/* ************************************************************************
	Deque Functions
************************************************************************ */

/* Initialize deque.

	param: 	q		pointer to the deque
	pre:	q is not null
	post:	q->Sentinel is allocated and q->size equals zero
*/
void _initCirListDeque (struct cirListDeque *q) 
{
	q->Sentinel = malloc(sizeof(struct DLink));
	assert(q->Sentinel != 0);
	q->Sentinel->next = q->Sentinel;
	q->Sentinel->prev = q->Sentinel;
	q->size = 0;
}

/*
 create a new circular list deque
 
 */

struct cirListDeque *createCirListDeque()
{
	struct cirListDeque *newCL = malloc(sizeof(struct cirListDeque));
	_initCirListDeque(newCL);
	return(newCL);
}


/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{
	struct DLink *newLink = malloc(sizeof(struct DLink));
	newLink->value = val;					//insert the value
	return newLink;	 

}

/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	v		value of the new link to be added after the existing link
	pre:	q is not null
	pre: 	lnk is not null
	pre:	lnk is in the deque 
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE val)
{
	struct DLink *newLink = malloc(sizeof(struct DLink));
	newLink = _createLink(val);
	newLink->prev = lnk;
	newLink->next = lnk->next;	//Insert newLink after existing lnk
	lnk->next->prev = newLink;  //thing after link's prev points at newlnk
	lnk->next = newLink;		//lnk now points to newlink in the list
	q->size++;								//Increment list size;

}

/* Adds a link to the back of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val) 
{
	struct DLink *newLink = malloc(sizeof(struct DLink));
	newLink = _createLink(val);

	_addLinkAfter(q, q->Sentinel, val);

	//newLink->prev = q->Sentinel->prev;
	//newLink->next = q->Sentinel;				//Insert lnk at back
	//q->Sentinel->prev->next = newLink;			//What pointed originaly to link l now points at the new link
	//q->Sentinel->prev = newLink;
	//q->size++;								//Increment list size;

}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{
	struct DLink *newLink = malloc(sizeof(struct DLink));
	newLink = _createLink(val);

	_addLinkAfter(q, q->Sentinel->prev, val);

	//newLink->next = q->Sentinel->next;
	//newLink->prev = q->Sentinel;			//Insert lnk at front
	//q->Sentinel->next->prev = newLink;	
	//q->Sentinel->next = newLink;			//What pointed originaly to link l now points at the new link
	//q->size++;								//Increment list size;


}

/* Get the value of the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q) 
{

	assert(q->Sentinel->next != q->Sentinel->prev);
	return(q->Sentinel->prev->value);
}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
	assert(q->Sentinel->next != q->Sentinel->prev);
	return(q->Sentinel->next->value);
}

/* Remove a link from the deque

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{	
	assert(lnk != NULL);
	lnk->prev->next = lnk->next;
	lnk->next->prev = lnk->prev;	//Dissasociate link
	free(lnk);						//free the link memory
	q->size--;						//Decrement list size;	 

}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q) {
	assert(q->Sentinel->prev != q->Sentinel);
	_removeLink(q, q->Sentinel->prev);

}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{

	assert(q->Sentinel->next != q->Sentinel);
	_removeLink(q, q->Sentinel->next);
}

/* De-allocate all links of the deque

	param: 	q		pointer to the deque
	pre:	none
	post:	All links (including Sentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{
	while (isEmptyCirListDeque(q) == 1) {
		/* remove the link right after the first sentinel */
		_removeLink(q, q->Sentinel->next);
	}
	/* remove the first and last sentinels */
	free(q->Sentinel);
	
}

/* 	Deallocate all the links and the deque itself. 

	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	the memory used by v->data is freed
*/
void deleteCirListDeque(struct cirListDeque *q) {
	assert(q != 0);
	freeCirListDeque(q);
	free(q);
}

/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) {
	if (q->Sentinel->next == q->Sentinel)
	{
		return(1);
	}
	return(0);
}

/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
	assert(q->Sentinel->next != q->Sentinel);
	int i = 0;
	struct DLink *printer = malloc(sizeof(struct DLink));
	printer->next = q->Sentinel->next;
	while (printer->next != q->Sentinel)
	{
		i++;
		printf("List value %d: %f \n", i, printer->next->value);
		printer->next = printer->next->next;
	}

	free(printer);

}

/* Reverse the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the deque is reversed
*/
void reverseCirListDeque(struct cirListDeque *q)
{	
	assert(q->Sentinel->next != q->Sentinel);
	struct DLink *temp = malloc(sizeof(struct DLink));
	struct DLink *rev = malloc(sizeof(struct DLink));
	temp->next = q->Sentinel->next;
	while (temp->next != q->Sentinel)
	{
		rev->next = temp->next->next;
		temp->next->next = temp->next->prev;
		temp->next->prev = rev->next;
		temp->next = rev->next;
		
	}
	temp->next = q->Sentinel->next;
	q->Sentinel->next = q->Sentinel->prev;
	q->Sentinel->prev = temp;


}

