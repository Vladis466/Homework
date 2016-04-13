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
#include <string>

using namespace std;






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
** Function: numCheckfin
** Description: Checks to see if the final grade is a number between 0 and 100
** Parameters: fin_Score: The score you receive on your final. The default is 0
			   dummy: A boolean you will kick out, denoting whether or not to proceed with the function.
** Pre-Conditions: existFin must be a number of type float
** Post-Conditions: Returns your final Score. It will be a number of type float.
*********************************************************************/ 
float numCheckfin(float score,bool& dum ) {
	if (score > 100 || score < 0 ) { 
	cout << "wrong input, please try again" << endl;
	dum = false;
	}
	return dum;
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
float fin_Range(int existFin, string msg) {
	/* The variable that will take the user input for the test score declared*/
	string finScore;
	float fin_Score = 0;
	/* Dummy declaration to check that the input is an integer*/
	bool dummy = false;
	/* if the user didnt put in 0 there is a final */
	if (existFin != 0) {
	
		cout << "Enter the score " << msg << endl;
		while (dummy == false) {
		
			cin   >> finScore;
			/* If the digit-checker approves the input, turn it into a float and break out of the loop*/
				if(digCheck(finScore)){ 
				fin_Score = atof(finScore.c_str() );
				dummy = true;
				numCheckfin(fin_Score, dummy);
				}
			}
		
	}   else {
	
	}
	/* Return the score on the final. If there isn't one it defaults to 0*/
	return fin_Score;
}

/*********************************************************************
** Function: Amt_Range
** Description: Checks that the amount of each input is a valid number
** Parameters: amount: Amount of tests/quizzes/etcc..
**			   quantitytransformation: the score you received transformed into a float if it is a number.
**			   existFin: This variable denotes whether or not there is a final in the class.
** Pre-Conditions: amount must exist as a string and be a valid integer 
** Post-Conditions: Returns your transformed score as an integer. It will be an integer value.
*********************************************************************/ 
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
** Function: get_num_weights
** Description: Takes in the percentage weight of each factor as a whole number
** Parameters: The test weight assignment weight lab weight final weight and quiz weight are all
** inputs within the function. 
** Pre-Conditions: Values inserted must be whole integers
** Post-Conditions: All inputs must be set to exit function.
*********************************************************************/ 
void get_num_weights(int& testweight, int& quizweight, int& assignweight, int& labweight, int& finalweight, int finGrade) {
	finalweight = 0;
	cout << "If your total isn't 100, you will have to re enter your values" << endl << endl;
	do {
	cout << "start here" << endl << endl;
	cout << "type in the the percentage  weight of the tests as a whole number percentage" << endl;
	testweight = fin_Range(1, "");
	cout << "type in the the percentage weight of quizzes the as a whole number percentage" << endl;
	quizweight = fin_Range(1, "");;
	cout << "type in the the percentage weight of the assignments as a whole number percentage" << endl;
	assignweight = fin_Range(1, "");;
	cout << "Type in the percentage weight of the labs as a whole number percentage" << endl;
	labweight = fin_Range(1, "");;
	if ( finGrade != 0) {
		cout << "type in the percentage weight of the final as a whole number" << endl;
	finalweight = fin_Range(1, "");;
	}
	} while (testweight + quizweight + assignweight + labweight + finalweight != 100);
}


/*********************************************************************
** Function: main
** Description: The main function maining on all main things. Very powerful.
** Parameters: Here we declare all variables that will be filled wth the weights 
** and number of inputs from each type. 
** Pre-Conditions: Initiation, no preconditions.
** Post-Conditions: No conditions need to be held.
*********************************************************************/ 
int main(int argc, const char *argv[]) {
	//Declaring variables and giving them arbitrary values, The dummy is to hold variables while they are converted
	string dummy;
	int tests = 0, quizzes = 0, assignments = 0, labs = 0, fin = 0;
	int testweight = 0, quizweight = 0, assignweight = 0, labweight = 0, finweight = 0;
	int counter = 1;

	while ( counter < argc)  {
		if (argv[counter] == string("-t")) {
			dummy = argv[counter + 1];
			tests = Amt_Range(dummy, "tests");
			counter+=2;
			
		} else if (argv[counter] == string("-q")) {
			dummy = argv[counter + 1];
			quizzes = Amt_Range(dummy, "quizzes");
			counter+=2;
			
			
		} else if (argv[counter] == string("-a")) {
		    dummy = argv[counter + 1];
			assignments = Amt_Range(dummy, "assignments");
			counter+=2;
		
			
		} else if (argv[counter] == string("-l")) {
		    dummy = argv[counter + 1];
			labs = Amt_Range(dummy, "labs");
			counter+=2;
	
			
		} else if (argv[counter] == string("-f")) {
		    dummy = argv[counter + 1];
			fin = Amt_Range(dummy, "whether there is a final");
			counter+=2;
		
		} else {
		cout << "wrong input NOW START OVER" << endl;
		exit(EXIT_FAILURE);
	
		}
	}
	
	// This function gets the number of tests quizzes assignments, labs and if there is a final from the user
	get_num_weights(testweight, quizweight, assignweight, labweight, finweight, fin);
	/* Calculates the weighted scores for each average and then sums them to find your overall expected grade
	** The inner function checks that the value is in range
	*/
	calculate_average(  fin_Range(fin, "for the final"), inRange(labs, "lab"),  inRange(assignments, "assignment"), inRange(quizzes, "quiz"), inRange(tests, "test"), testweight, quizweight, assignweight, labweight, finweight);
	
	return 0;	
}