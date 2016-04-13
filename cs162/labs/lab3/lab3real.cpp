#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <istream>
#include <string>


using namespace std;

class Items { 
	private:
		string Name;
		string Unit;
		int Quantity;
		float Price;
		
 	public:
		void getName(string myName){
			Name = myName;
		}
		void getUnit(string myUnit){
			Unit = myUnit;
		}
		void getQuantity(int myQuantity){
			Quantity = myQuantity;
		}
		void getPrice(float myPrice){
			Price = myPrice;
		}
		void printItem(){
			cout << "Name: " <<  Name << endl << "Unit: " << Unit << endl 
			<< "Quantity: " << Quantity << endl << "Price: " << Price << endl;
		}
	
};



/* void addItem(Items itemList[50]) {
	for (int i = 0; i < 50; i++){ 
		if (itemList[i] == "0" && itemlist[i] != itemList[i + 1]) {
			cin >> itemList[i].Name;
			cin >> itemList[i].Unit;
			cin >> itemList[i].Quantity;
			cin >> itemList[i].Price;
			}
		}
} 
	 */
	 
void Add_item(Items *list, int members){	
	string name, unit;
	int quantity;
	float price;
	for(int i=0; i<members; i++){
			cout << "Insert the name of your item" << endl;
			cin >> name;
			cout << "Insert the units" << endl;
			cin >> unit;
			cout << "Insert the quantity" << endl;
			cin >> quantity;
			cout << "Insert the price" << endl;
			cin >> price;
			list[i].getName(name);
			list[i].getUnit(unit);
			list[i].getQuantity(quantity);
			list[i].getPrice(price);
			
	}	
}

void Extra_item(Items *list){	
	
	string name, unit, dummy;
	int quantity, placement;
	float price;
	dummy = "y";
	
	while (dummy == "y") {
		cout << "Would you like to add another item to your list? (press y or n)" << endl;
		cin >> dummy;
		
		if (dummy == "n") {
			break;
		}
		
	cout << "Choose a position on your list for this member, one already filled will result in an overwrite" << endl;
	cin >> placement;
		

		
		
			cout << "Insert the name of your item" << endl;
			cin >> name;
			cout << "Insert the units" << endl;
			cin >> unit;
			cout << "Insert the quantity" << endl;
			cin >> quantity;
			cout << "Insert the price" << endl;
			cin >> price;
			list[placement - 1].getName(name);
			list[placement - 1].getUnit(unit);
			list[placement - 1].getQuantity(quantity);
			list[placement - 1].getPrice(price);
	} ;	
		
}


void Remove_item(Items *list){
	
	string name, unit, dummy;
	int quantity, placement;
	float price;
	dummy = "y";
	
	while (dummy == "y") {
		cout << "Would you like to remove an item from the list? (press y or n)" << endl;
		cin >> dummy;
		
		if (dummy == "n") {
			break;
		}
		
		cout << "Which item number would you like to remove?" << endl;
		cin >> placement;
		
		list[placement - 1].getName("0");
		list[placement - 1].getUnit("0");
		list[placement - 1].getQuantity(0);
		list[placement - 1].getPrice(0);
	} ;
	
}

Items* create_table(int memberss) {
  
	Items* list = new Items[50];
	//for(int i = 0; i < rows; i++) {
        //table[i] = new mult_div_values[cols]; 
    //}
	return list;
}



int main() {
	int members;
	int dummy;
	cout << "insert number of items on the list" << endl;
	cin >> members;
	
	Items* itemList = create_table(members);
	
	Add_item(itemList, members);
	
	cout << "What item on the list would you like to list,(Press: 1 2 3 4...etc)" << endl;
	cin >> dummy;
	itemList[dummy - 1].printItem();
	
	Extra_item(itemList);
	
		
	for(int i = 0; i < 50; i++) {

		itemList[i].printItem();
	}
	
	Remove_item(itemList);
	
	for(int i = 0; i < 50; i++) {

		itemList[i].printItem();
	}
	
	return 0;
}


