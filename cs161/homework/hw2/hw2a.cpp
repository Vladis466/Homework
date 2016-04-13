

/***********************
 ** program: hw2.cpp
 ** Author: Vlad Predovic
 ** Date: 10/23/2014
 ** Description: Adds flexibility to outputting test score average making sure scores are from 1-100
 ** user can input as many scores as he wants, and checking for valid inputs(no letters.)
 ** Input: test averages for 5 seperate tests
 ** Output: test average for 5 scores in decimal binary hexadecimal and octal forms
************************/
 
#include <iostream>
#include <limits.h>
#include <math.h>
#include <iomanip>
#include <stdlib.h>
#include <ctype.h>
using namespace std;

int main() {

	cout << endl;

/* variable used to find how many test scores will be input*/ 	
int n;


/* prompt user for amount of tests to enter */ 
	cout <<  "How many tests are you going to enter?" << endl;
	cin >> n;
	
/* variable for size of array of test scores */
string testscores[n][100];
/*variable to find the average of inputted values*/
int total = 0;
	
/* prompt user for n test scores and then save them in the array test scores */
	cout <<  "Insert your " << n << " test scores" << endl;
	
	/* this next part asks the user to input the test scores and it then puts them into an array 
	of size n which the user initially specified. */
	for (int i = 0; i <= n - 1 ; i++) {
		cin >> testscores[i];
		
		/*make sure each test score entered is between 1 and 100*/
		if (find_if(testscores[i].begin(), testscores[i].end(), isdigit) == false ) {
			
			/* This c'inpode will sum the values of all the test scores as you input them if they are valid.*/
			cout << "input is not a number"<< endl;
			
	}	
		int testNum= atoi.testscores[i];
		
		else if  (testNum > 100 && testNum < 0 ) {
	
			/* If the input isnt accepted then this code will kick you back to the beginning of the loop*
			asking you to repeat the input for that spot in the array.*/
			cout << "wrong input, please try again" << endl;
	}	
		else if {
				total += testNum;
		}
	
}
/* find the average test score*/
	total = total/n;
	cout << endl;
	cout << total << endl;
	
	
	return 0;
}

/*start from here!! Get necessary data from hw1 file

&& isdigit(testscores[i])
b = testscores[i]; 
b = atoi testscores[i]; 
if (testscores[i] <= 100 && testscores[i] >= 0 ) { */

