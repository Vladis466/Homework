/***********************
 ** program: hw3.cpp
 ** Author: Vlad Predovic
 ** Date: 10/23/2014
 ** Description: Adds onto hw2, providing separate functions for each step in the process in order to organize
 ** the data better.
 ** Input: Amount and weights of tests, quizzes, assignments, labs, and whether or not there is a final.
 ** Output: The average grade yo are going to get in a class.
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


/*********************************************************************
** Function: get_num_tests 
** Description: Gets the number of tests, quizzes, assignments, labs, and whether there is 
** a final in this class
** Parameters: the number of tests 
** Pre-Conditions: The number inserted must be an integer. You cannot take half a test.
** Post-Conditions: All inputs must be responded to to exit function
*********************************************************************/ 
void get_num_tests(int& tests, int& quizzes, int& assignments, int& labs, int& finale) {

	cout << "type in the number of tests" << endl;
	cin >> tests;
	cout << "type in the number of quizzes" << endl;
	cin >> quizzes;
	cout << "type in the number of assignments" << endl;
	cin >> assignments;
	cout << "Type in number of labs" << endl;
	cin >> labs;
	cout << "Is there a final? (0 for no, Anything else means yes ;))";
	cin >> finale;
}

/*********************************************************************
** Function: get_num_weights
** Description: Takes in the percentage weight of each factor as a whole number
** Parameters: The test weight assignment weight lab weight final weight and quiz weight are all
** inputs within the function. 
** Pre-Conditions: Values inserted must be whole integers
** Post-Conditions: All inputs must be set to exit function.
*********************************************************************/ 
void get_num_weights(int& testweight, int& quizweight, int& assignweight, int& labweight, int& finalweight, int finGrade) {

	cout << "type in the the percentage  weight of the tests as a whole number percentage" << endl;
	cin >> testweight;
	cout << "type in the the percentage weight of quizzes the as a whole number percentage" << endl;
	cin >> quizweight;
	cout << "type in the the percentage weight of the assignments as a whole number percentage" << endl;
	cin >> assignweight;
	cout << "Type in the percentage weight of the labs as a whole number percentage" << endl;
	cin >> labweight;
		if ( finGrade != 0) {
		cout << "type in the percentage weight of the final as a whole number" << endl;
		cin >> finalweight;
		}
}


/*********************************************************************
** Function: digCheck
** Description: A boolean function that checks if an input is a digit
** Parameters: a: dummy variable representing each index in the string input.
** 			   str: the score the user used as an input
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/ 
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


/*********************************************************************
** Function: inRange
** Description: The amount of tests/quizzes/assignments (n) you want to input
** Parameters: n: Represents the amount of tests/quizzes etc to input
**			   testNum: A dummy variable to help add up the test inputs
**			   i: The counter to repeat the input loop the amount of times n
** 			   total: Every input gets added into this variable to get your average score
** Pre-Conditions: User inputs the number of tests/quizzes/etc to take. Input must be an integer
** Post-Conditions: output will not necessarily be an integer. Output will be a number.
*********************************************************************/ 
float inRange(int n, string msg) {	
	
	/* variable for size of array of test scores */
	string testscores[n];
	/*variable to find the average of inputted values*/
	float total = 0;
	/* prompt user for n test scores and then save them in the array test scores */
	cout <<  "Insert your " << n << " " << msg << " scores" << endl;
	/* this next part asks the user to input the test scores and it then puts them into an array 
	of size n which the user initially specified. */
	int i =0;
	while (i < n ) {  
		cin >> testscores[i];
		/* This creates an infinite loop until the if statement returns true*/
		if(digCheck(testscores[i])){ 
			float testNum = atof(testscores[i].c_str() );		
			/*make sure each test score entered is between 1 and 100. Otherwise
			//this code will kick you back to the beginning of the loop
			//asking you to repeat the input for that spot in the array.
			*/
			if (testNum > 100 || testNum < 0 ) { 
				cout << "wrong input, please try again" << endl;
		}	else  {		
				/* This code will sum the values of all the test scores as you input them if they are valid.*/
				i+=1;
				total += testNum;				
		}		
	}
	}
	/* find the average test score*/
	total = total/n; return total;
}

/*********************************************************************
** Function: fin_range
** Description: Checks if there is a final grade and if there s it asks you what the final grade is.
** Parameters: finScore: The score you receive on your final. The default is 0
			   fin_score: the score you recieved transformed into a float if it is a number.
**			   existFin: This variable denotes whether or not there is a final in the class.
** Pre-Conditions: existFin must be a whole number 
** Post-Conditions: Returns your final Score. It will be an integer value.
*********************************************************************/ 
float fin_Range(int existFin) {
	/* The variable that will take the user input for the test score declared*/
	string finScore;
	float fin_Score = 0;
	/* Dummy declaration to check that the input is an integer*/
	bool dummy = false;
	/* if the user didnt put in 0 there is a final */
	if (existFin != 0) {
	
		cout << "Enter the score for the final " << endl;
		while (dummy == false) {
		
			cin   >> finScore;
			/* If the digit-checker approves the input, turn it into a float and break out of the loop*/
				if(digCheck(finScore)){ 
				fin_Score = atof(finScore.c_str() );
				dummy = true;
				break;
				}
			}
		
	}   else {
	
	}
	/* Return the score on the final. If there isn't one it defaults to 0*/
	return fin_Score;
}


	
/*********************************************************************
** Function: calculate_average 
** Description: Finds the weighted average of your scores and sums them to find your score in the class
** Parameters: Takes in the average score and class weights for the final, lab, assignments, quizzes, and tests
** Pre-Conditions:  All values taken in by the function are either integers or floats
** Post-Conditions: Will kick out your average score to the console
*********************************************************************/ 	
void calculate_average(float finalScore, float labScores, float assignScores, float quizScores, float testScores,int testweight, int quizweight, int assignweight, int labweight, int finalweight) {
	
	testScores = testScores*testweight/100;
	quizScores = quizScores*quizweight/100;
	assignScores = assignScores*assignweight/100;
	labScores = labScores*labweight/100;
	finalScore = finalScore*finalweight/100;
	
	
	float average = testScores + quizScores + assignScores + labScores + finalScore; 
	
	cout << "The average score you are going to get in this class is " << average << "%" << endl;
}



/*********************************************************************
** Function: main
** Description: The main function maining on all main things. Very powerful.
** Parameters: Here we declare all variables that will be filled wth the weights 
** and number of inputs from each type. 
** Pre-Conditions: Initiation, no preconditions.
** Post-Conditions: No conditions need to be held.
*********************************************************************/ 
int main() {
	//Declaring variables and giving them arbitrary values
	int tests = 2, quizzes = 2, assignments = 2, labs = 2, fin = 2;
	int testweight = 2, quizweight = 2, assignweight = 2, labweight = 2, finweight = 2;
	
	// This function gets the number of tests quizzes assignments, labs and if there is a final from the user
	get_num_tests(tests, quizzes, assignments, labs, fin);
	get_num_weights(testweight, quizweight, assignweight, labweight, finweight, fin);
	/* Calculates the weighted scores for each average and then sums them to find your overall expected grade
	** The inner function checks that the value is in range
	*/
	calculate_average(  fin_Range(fin), inRange(labs, "lab"),  inRange(assignments, "assignment"), inRange(quizzes, "quiz"), inRange(tests, "test"), testweight, quizweight, assignweight, labweight, finweight);
	
	return 0;	
}