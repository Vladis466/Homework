/***********************
 ** program: hw4.cpp
 ** Author: Vlad Predovic
 ** Date: 10/23/2014
 ** Description: Adds onto hw3, allowing you to insert values from the command line. 
 ** It will also error check EVERYTHING WHICH IS AWEESOME.
 ** Input: Amount and weights of tests, quizzes, assignments, labs, and whether or not there is a final.
 ** Output: The average grade yo are going to get in a class.
************************/
 
#include <iostream>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include<ctime>
#include<string>

using namespace std;
//Will create 2d Dynamic Array and initialize it with random values
int** create_arr(int row, int col){
   int **array;
   cout << "printing square array of row and column length " << row << endl;
   array = new int*[row];
   for(int i = 0; i < row; ++i){
      array[i] = new int[col];
   }
   for (int i = 0; i < row; ++i){
      for (int j = 0; j < col; ++j){
	 array[i][j] = rand() % 10;
	 cout << array[i][j] << " ";
      }
      cout << endl;
   }
   cout << endl;
   return array;
}

//Will create uninitialized 2d Dynamic Array
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
void recursive_calculate_result(int **array1, int **array2, int i, int j, int length){
	
    if (i < length ) {
        if (j < length ) {
            array2[i][j] = array1[i][j] + array1[i+1][j] + array1[i][j+1] + array1[i+1][j+1];
            recursive_calculate_result(array1, array2, i, j + 1, length);
        } else {
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

int main() {
	int dummy = 7;
	int arrSize;
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

