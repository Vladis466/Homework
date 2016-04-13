#include <iostream>
#include <stdlib.h>
#include <string>
#include "./lab1x.h"

using namespace std;

int main(int argc, char *argv[]) {

	string dummy1, dummy2;
	int rows, cols;
	dummy1 = argv[1];
	dummy2 = argv[2];
	
	rows = Amt_Range(dummy1, "rows"); 
	cols = Amt_Range(dummy2, "columns");
	
	mult_div_values** table= create_table(rows,cols);
	
	set_mult_values(table, rows, cols);
	
	set_div_values(table, rows, cols);
	
	printarray(rows,cols,table);
		
/* 	cout << endl << endl;
	cout << rows << endl;
	cout << cols << endl; */

return 0;
}