#include <iostream>
#include <stdlib.h>
#include <string>
#include "lab1x.h"

using namespace std;


	
	
	float numCheckfin(float score,bool& dum ) {
	if (score <= 0) { 
	cout << "Wrong input, please try again" << endl;
	dum = false;
	}
	return dum;
}

bool digCheck(string str){
	/*This code is to cycle through each index of each array input looking for a non-numeric input*/
	for(int a = 0 ; a < str.length() ; a++){
		/* If the input is not a valid number this will return false and kick you out of the function*/
		if (isdigit(str[a]) == false){		
			cout << "Input is not a valid number, please try again"<< endl;			
			return false;
		} 
	}
	return true;
}

float Amt_Range(string &amount, string msg) {
	/* The variable that will take the user input for the test score declared*/
	
	int quantitytransformation = 0;
	/* Dummy declaration to check that the input is an integer*/
	bool dummy = false;
	
	if(digCheck(amount)){ 
		quantitytransformation = atof(amount.c_str() );
		dummy = true;
		numCheckfin(quantitytransformation, dummy);
		}
	
	/* if the user didnt put in 0 there is a final */
	while (dummy == false) {
		cout << "The value you entered for the amount of " << msg << " is invalid enter another please" << endl;
			
		cin >> amount;
		/* If the digit-checker approves the input, turn it into a float and break out of the loop*/
			if(digCheck(amount)){ 
			quantitytransformation = atof(amount.c_str() );
			dummy = true;
			numCheckfin(quantitytransformation, dummy);
			}
	}
		
	/* Return the score on the final. If there isn't one it defaults to 0*/
	return quantitytransformation;
}



	


void printarray(int m, int n, mult_div_values **table)
{

	for(int i=0; i<m; i++)
	{
		for(int j=0; j<m; j++)
		{
			cout << table[i][j].mult << " ";
		}
		cout << endl;
	}
	cout << endl << endl << "div table below" << endl;
	
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<m; j++)
		{
			cout << table[i][j].div << " ";
		}
		cout << endl;
	}
} 

mult_div_values** create_table(int rows, int cols) {
  
	mult_div_values** table = new mult_div_values*[rows];
	for(int i = 0; i < rows; i++) {
        table[i] = new mult_div_values[cols]; 
/*         for(int j = 0; j < cols; j++){
		table[i][j] = new mult_div_values*;
		} */    
    }
	return table;
}

void set_mult_values(mult_div_values **table, int m, int n)
{	
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n;  j++)
		{
			table[i][j].mult = (i + 1) * (j + 1);
		}
	}
}

void set_div_values(mult_div_values **table, int m, int n)
{

	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
			table[i][j].div = (((float)(i + 1)) / (float)(j + 1));
		}
	}
}



	
	
	
