/* CS261- Assignment 1 - Q.3*/
/* Name: Vlad Predovic , kevin Silker
 * Date: 4/7/2015
 * Solution description: Fills and sorts an array of random numbers
 * Visual Studio 2013
 */
 
#include <stdio.h>
#include <stdlib.h>

/*Runs through a loop that will sort a
list of number is ascending order and return 
it to main. 
preconditions: int pointer and a int representing size
postconditions: none. Returns sorted array*/
void sort(int* number, int n){
	int temp;
	int x;
	int b;
     /*Sort the given array number , of length n*/   
	for (b = 0; b < 10; b++){   /*sort algorithm is not perfect so run through a few times*/
		for (int i = 0; i < n; i++){  /*sort for every int*/
			x = i;
			while (i < 20){       /*compare with all other ints */
				if (i == 19){	/*so we dont go out of bounds*/
					break;
				}
				if (number[i] > number[i + 1]){   /*sort algorithm*/
					temp = number[i + 1];
					number[i + 1] = number[i];
					number[i] = temp;
				}
				i++;
			}
			i = x;		/*reusing variables*/
		}
	}



}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
	int n = 20;
	int *arr;
    /*Allocate memory for an array of n integers using malloc.*/
	 arr = (int *)malloc(n*4);
    /*Fill this array with random numbers between 0 and n, using rand().*/
	 for (int i = 0; i < n; i++){
		 arr[i] = rand() % n;
	 }
    /*Print the contents of the array.*/
	 for (int i = 0; i < 20; i++){
		 printf(" position%d: %d\n", i, arr[i]);
	 }
    /*Pass this array along with n to the sort() function.*/
	 sort(arr, n);

	 printf("\n");
	 printf(" Sorted array below: \n");

    /*Print the contents of the array.*/ 
	 for (int i = 0; i < 20; i++){
		 printf(" position%d: %d\n", i, arr[i]);
	 }
    return 0;
}
