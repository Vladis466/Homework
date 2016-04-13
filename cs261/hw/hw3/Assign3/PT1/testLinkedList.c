#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>


void assertTrue(int predicate, char *message)
{
	printf("%s: ", message);
	if (predicate)
		printf("PASSED\n");
	else
		printf("FAILED\n");
}

int main(int argc, char* argv[]) {
    
	struct linkList *newList;
	newList = createLinkedList();
	assertTrue(EQ(isEmptyList(newList), 1), "The list is empty");

	printf("\n\nTesting addFrontList #'s: 1, 2, 3, 4 \n");
	addFrontList(newList, 1);
	addFrontList(newList, 2);
	addFrontList(newList, 3);
	addFrontList(newList, 4);
	printf("Numbers should be in descending order because the function adds at the front\n");
	printList(newList);

	printf("\n\nTesting size = 4 \n");


	assertTrue(EQ(frontList(newList), 4), "\n\nTest 1st element in the deque == 4");
	assertTrue(EQ(isEmptyList(newList), 0), "Testing isEmptyList. The list is not empty");

	printf("\n\nTesting addBackList by adding 8 & 9 \n");
	printf("printList should print [ 4, 3, 2 , 1, 8, 9] \n");
	addBackList(newList, 8);
	addBackList(newList, 9);
	printList(newList);

	assertTrue(EQ(containsList(newList, 8), 8), "Testing containsList. search for 8");

	printf("\n\nTesting removeFrontList by taking off two terms from the front \n");
	removeFrontList(newList);
	removeFrontList(newList);
	printf("Testing removeBackList by taking off two terms from the back\n");
	removeBackList(newList);
	removeBackList(newList);
	printf("printList should print [ 2 , 1] \n");
	printList(newList);

	printf("\n\nTesting removeList by searching for 1 and taking it off. printList will now only print [ 2 ] \n");
	removeList(newList, 1);
	printList(newList);
	



	return 0;
}


