/* CS261- Assignment 1 - Q. 0*/
/* Name: Vlad Predovic
 * Date: April 10th 2015
 * Solution description: Prints the unique parts of a pointer.
 * Visual Studio 2013
 */
 
#include <stdio.h>
#include <stdlib.h>

/*Prints values.
preconditions: int pointer
postconditions: none.*/
void fooA(int* iptr){
     /*Print the value of the integer pointed to by iptr*/
	printf("The value of x pointed to by iptr is %d\n", *iptr);
		/*Print the address pointed to by iptr*/
	printf("The value of the address pointed to by iptr is %p\n", iptr);
     /*Print the address of iptr itself*/
	printf("The address of iptr is %p\n", &iptr);
}

int main(){
    
    /*declare an integer x*/
	int x = 10;
	int *ptr;
	ptr = &x;
    /*print the address of x*/
	printf("The address of x: %p\n", &x);
    /*Call fooA() with the address of x*/
	fooA(ptr);
    /*print the value of x*/
	printf("The value of x: %d\n", x);
    return 0;
}
