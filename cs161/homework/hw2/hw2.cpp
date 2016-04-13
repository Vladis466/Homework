



/***********************
 ** program: hw2.cpp
 ** Author: Vlad Predovic
 ** Date: 10/23/2014
 ** Description: Adds flexibility to outputting test score average making sure scores are from 1-100
 ** user can input as many scores as he wants, and checking for valid inputs(no letters.)
 ** Input: test averages for n separate tests
 ** Output: test average for n scores in decimal binary hexadecimal and octal forms
************************/
 
#include <iostream>
#include <limits.h>
#include <math.h>
//#include <iomanip>
#include <stdlib.h>
//#include <ctype.h>
//#include <algorithm>
//#include <string>

using namespace std;

int main() {

	cout << endl;

	/* variable used to find how many test scores will be input*/ 	
	int n;

	
	/* prompt user for amount of tests to enter */ 
	cout <<  "How many tests are you going to enter?" << endl;
	cin >> n;
	
	/* variable for size of array of test scores */
	string testscores[n];
	/*variable to find the average of inputted values*/
	float total = 0;
	
	/* prompt user for n test scores and then save them in the array test scores */
	cout <<  "Insert your " << n << " test scores" << endl;
	
	/* this next part asks the user to input the test scores and it then puts them into an array 
	of size n which the user initially specified. */
	for (int i = 0; i <= n - 1 ; i = i + 1) {

		cin >> testscores[i];
		
		
		/*This code sets the value that will loop through each test entry to check for validity*/
		for(int a = 0 ; a < testscores[i].length() ; a++){
			
			/*This code is to cycle through each index of each array input looking for a non-numeric input*/
			if (isdigit(testscores[i][a]) == false){
				
				cout << "Input is not a valid number, please try again"<< endl;
				
				
				/* go back one test to check for input*/
				i = i - 1;
				
				/* this if statement chooses whether to blank out the spot in the array or just break the 
				// code directly so that you do not get an error due to negative dummy var in case of first
				// input being not a number. 
				*/
				
				if (i != -1) { 
				
				/*reset the value of the test so that it doesn't keep adding on*/
				testscores[i] = 1;
				} else {	
				/*break out of this if statement!*/
				break;
				
				}
			}	
			

		}	
	/* turn the string into a float so the logic will work for the next if statement*/	
	float testNum = atof(testscores[i].c_str() );
			
		/*make sure each test score entered is between 1 and 100*/
	    if (testNum > 100 || testNum < 0 ) {
	
			/* If the input isnt accepted then this code will kick you back to the beginning of the loop*
			asking you to repeat the input for that spot in the array.*/
			i = i - 1;
			cout << "wrong input, please try again" << endl;
		}	
		else  {
		
		/* This code will sum the values of all the test scores as you input them if they are valid.*/
			total += testNum;	
			
			/*cout << total << endl;*/

		}
			
		
		
		
	}
	/* find the average test score*/
	total = total/n;
	cout << endl;
	cout << total << endl;
	
	return 0;


}