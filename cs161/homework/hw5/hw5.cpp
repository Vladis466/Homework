/***********************
 ** program: hw5.cpp
 ** Author: Vlad Predovic
 ** Date: 10/23/2014
 ** Description: Creates a randomized 2 array of a size of your choosing. Then creates an
 ** array of n-1 size whose components are the sum of your arrays.
 ** Input: array size, whether to run the program recursively or not, and a number.
 ** Output: a 2d matrix of size n-1
************************/
 
#include <iostream>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include<ctime>
#include<string>

using namespace std;
//Will create 2d Dynamic Array and initialize it with random values
/*********************************************************************
** Function: create_arr
** Description: A boolean function that checks if an input is a digit
** Parameters: a: dummy variable representing each index in the string input.
** 			   str: the score the user used as an input
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/ 
int** create_arr(int row, int col){
   
   int dummy;
   cout << "Now pick a number!!" << endl;
   cin >> dummy;
   int **array;
   cout << "printing square array of row and column length " << row << endl;
   array = new int*[row];
   for(int i = 0; i < row; ++i){
      array[i] = new int[col];
   }
   for (int i = 0; i < row; ++i){
      for (int j = 0; j < col; ++j){
	 array[i][j] = rand() % dummy;
	 cout << array[i][j] << " ";
      }
      cout << endl;
   }
   cout << endl;
   return array;
}

//Will create uninitialized 2d Dynamic Array
/*********************************************************************
** Function: blankArray
** Description: Initializes a blank array of sizes n-1
** Parameters: n: the row and column size (square matrixes)
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/ 
int** blankArray(int row, int col){
   int **array;
   cout << "Creating blank array of row and column length " << row << endl;
   cout << endl;
   array = new int*[row];
   for(int i = 0; i < row; ++i){
      array[i] = new int[col];
   }
   return array;
}

/*********************************************************************
** Function: calculate_result
** Description: Calculates the result iteratively.
** Parameters: array1: The initial initialized array
** 			   array2: The second array that will be filled
**		 i, j, length: dummy variable representing each index in the string input.
** Pre-Conditions: Inputs are numbers
** Post-Conditions: Will output a matrix of n-1 n-1 to cout
*********************************************************************/ 
void calculate_result(int **array1, int **array2, int length){
	cout << "Displaying results for new 2d array iteratively" << endl;
	for (int i = 0; i < length - 1; ++i){
		for (int j = 0; j < length - 1; ++j){
		array2[i][j] = array1[i][j] + array1[i+1][j] + array1[i][j+1] + array1[i+1][j+1];
		cout << array2[i][j] << " ";
		}
	cout << endl;
	}
}

/*********************************************************************
** Function: recursive_calculate_result
** Description: calculates result recursively
** Parameters: array1: The initial initialized array
** 			   array2: The second array that will be filled
**		 i, j, length: dummy variable representing each index in the string input.
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/ 
void recursive_calculate_result(int **array1, int **array2, int i, int j, int length){
	
    if (i < length ) {
        if (j < length ) {
			//This will sum up the values of the 4 points into another value
            array2[i][j] = array1[i][j] + array1[i+1][j] + array1[i][j+1] + array1[i+1][j+1];
            recursive_calculate_result(array1, array2, i, j + 1, length);
        } else {
			//once the length - 1 is reached of the matrix it will complete the iteration
            recursive_calculate_result(array1, array2, i + 1, 0, length);
			
			for (int i = 0; i < length ; ++i){
				for (int j = 0; j < length ; ++j){
				cout << array2[i][j] << " ";
				}
			cout << endl;
			}
		exit(EXIT_FAILURE);
        }
    }
	
}

/*********************************************************************
** Function: main
** Description:Where everything is ran
** Parameters: dummy: whether to run iteratibe or not
** 			   arrSize:The size of the array
** Pre-Conditions: Inputs are numbers
** Post-Conditions: number inputs will for a 2d array
*********************************************************************/ 
int main() {
	int dummy = 7; int arrSize;
	cout << "what is the array size?"<< endl;
	cin >> arrSize;
	cout << "To recursive (press 1), or to not recursive (press 0)"  << endl;
	cin >> dummy;
	cout << endl;
	//create and initialize main array
	int **arr1 = create_arr(arrSize, arrSize);
	//create and second blank array
	int **arr2 = blankArray(arrSize-1, arrSize-1);
	
	if (dummy == 1) {
	calculate_result(arr1, arr2, arrSize);
	} else if (dummy == 0) {
	cout << "Displaying results for new 2d array indubitably recursively" << endl;
	recursive_calculate_result(arr1, arr2, 0, 0, arrSize - 1);
	} else {
	cout << "You obviously can't even" << endl;
	}
return 0;
}
