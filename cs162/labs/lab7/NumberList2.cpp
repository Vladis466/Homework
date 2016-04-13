#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <istream>

using namespace std;

class DoublyLinkedIntNode {
	public: 
		DoublyLinkedIntNode(){}
		DoublyLinkedIntNode(int theData, DoublyLinkedIntNode* previous, DoublyLinkedIntNode* next) 
			: data(theData), nextLink(next), previousLink(previous){} 
		DoublyLinkedIntNode* getNextLink() const { return nextLink; }
		DoublyLinkedIntNode* getPreviousLink() const { return previousLink; }
		
		int getData() const { return data;}
		void setData(int theData) { data = theData; }
		void setNextLink(DoublyLinkedIntNode* pointer) { nextLink = pointer; }
		void setPreviousLink(DoublyLinkedIntNode* pointer){ previousLink = pointer; }
		
	private: 
		int data;
		DoublyLinkedIntNode *nextLink;
		DoublyLinkedIntNode *previousLink;
};
typedef DoublyLinkedIntNode* DoublyLinkedIntNodePtr;



void headInsert(DoublyLinkedIntNodePtr& head, int theData){ //if i remover Ptr i get error? is this correct??
	
	DoublyLinkedIntNode* newHead = new DoublyLinkedIntNode(theData, NULL, head);
	head->setPreviousLink(newHead);
	head = newHead;
}



void deleteNode(DoublyLinkedIntNodePtr& head, DoublyLinkedIntNodePtr discard){ //semicolon before bracket? pg.757
	if(head == discard){
		head = head->getNextLink();
		head->setPreviousLink(NULL);
	}else{
		DoublyLinkedIntNodePtr prev = discard->getPreviousLink();
		DoublyLinkedIntNodePtr next = discard->getNextLink();
		prev->setNextLink(next);
		if(next != NULL){
			next->setPreviousLink(prev);
		}
	}
	delete discard;
}
	




main(){
	return 0;
}