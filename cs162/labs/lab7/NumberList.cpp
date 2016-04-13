#include "NumberList.h"
using namespace std;



//*****************************************************
// add adds a new element to the end of the list. *
//*****************************************************
void NumberList::add(double number)
{
	if (head == NULL)
		head = new ListNode(number);
	else {
		// The list is not empty.
		// Use nodePtr to traverse the list
		ListNode *nodePtr = head;
		while (nodePtr->next != NULL)
			nodePtr = nodePtr->next;
		
		// nodePtr->next is NULL so nodePtr points to the last node.
		// Create a new node and put it after the last node.
		nodePtr->next = new ListNode(number);
	}
}

//***************************************************
// displayListHead outputs a sequence of all values   *
// currently stored in the list starting at the Head. *
//***************************************************
void NumberList::displayListHead()
{
	ListNode *nodePtr = head;   // Start at head of list
	while (nodePtr)
	{
		// Print the value in the current node
		cout << nodePtr->value << "    ";
		// Move on to the next node
		nodePtr = nodePtr->next;
	}
}

//***************************************************
// displayListTail outputs a sequence of all values     *
// currently stored in the list starting at the Tail.   *
//***************************************************
void NumberList::displayListTail()
{
	ListNode *nodePtr = head;   // Start at head of list
	while (nodePtr)
	{
		// Print the value in the current node
		cout << nodePtr->value << "    ";
		// Move on to the next node
		nodePtr = nodePtr->next;
	}
}



//******************************************************
// Destructor deallocates the memory used by the list. *
//******************************************************
NumberList::~NumberList()
{
	ListNode *nodePtr = head;  // Start at head of list
	while (nodePtr != NULL)
	{
		// garbage keeps track of node to be deleted
		ListNode *garbage = nodePtr;
		// Move on to the next node, if any
		nodePtr = nodePtr->next;
		// Delete the "garbage" node
		delete garbage;
	}
}

int main()
{
	NumberList list;
	list.add(2.5);
	list.add(7.9);
	list.add(12.6);
	list.add(4.1);
	list.add(3.1);
	list.add(2.1);
	list.add(1.1);
	list.displayListHead();
	list.displayListTail();
	cout << endl;
	return 0;
}