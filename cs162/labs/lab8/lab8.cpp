#include <cstdlib>
#include <iostream>

using namespace std;

struct node{
	int data;
	node* next;  //nodes have the ability to point to next and 
	node* prev;	 //previous node
};

void PrintForward(node* head);
void QuirkulateAdd(node* head);
void Demoverizer(node* head);

int main(){
	node* head;  //marks beginning of list
	node* tail; //marks end of list
	node* n;
	node* m;
	
	n = new node; //creates a new node
	m = n;
	n->data = 1; //go and find node referenced by n pointer set data = 1
	n->prev = NULL; //make sure previous pointer not pointing anything cuz first
	head = n;      // equal to the node n is pointing to
	tail = n;	  // tail pointer pointing to same pointer
	
	n = new node;      //now n points to this new node
	n->data = 2;	  
	n->prev = tail;   //the pointer inside the node n is pointing to now points to tail of first node
	tail->next = n;  //make 1st node link to 2nd via 1st nodes 1st pointer 
	tail = n;		//now we want tail to mark end of doubly linked list
	
	n = new node;
	n->data = 3;
	n->prev = tail;
	tail->next = n;
	tail = n;
	
	n = new node;
	n->data = 0;
	n->prev = tail;
	tail->next = n;
	tail = n;
	
	n = new node;
	n->data = 0;
	n->prev = tail;
	tail->next = n;
	tail = n;
	
	n = new node;
	n->data = 0;
	n->prev = tail;
	tail->next = n;
	tail = n;
	
	n = new node;
	n->data = 0;
	n->prev = tail;
	tail->next = n;
	tail = n;
	
	n = new node;
	n->data = 0;
	n->prev = tail;
	tail->next = n;
	tail = n;
	
	n = new node;
	n->data = 0;
	n->prev = tail;
	tail->next = n;
	tail = n;
	tail->next = head;
	
	m->prev = tail; //make sure previous pointer not pointing anything cuz first
	
	QuirkulateAdd(head);
	QuirkulateAdd(head);
	QuirkulateAdd(head);
	Demoverizer(head);
	PrintForward(head);
	
	return 0;
	
}

void QuirkulateAdd(node* head){
	int ins;
	int dummy = 0;
	cout << "Insert thy additive value" << endl;
	cin >> ins;
	node *temp = head;
	while (temp->data != 0 && dummy == 0){
	temp = temp->next;
	}
	if (temp->data == 0){
		temp->data = ins;
		dummy == 1;
	}
}

void Demoverizer(node* head){
	node* q;  //dummy node
	head->data = 0;
	head->next = head;
}

void PrintForward(node* head){
	node* temp = head;
	while(temp->data != 0){
	cout << temp->data << " ";
	temp = temp->next;
	}
	cout << endl;
}

	