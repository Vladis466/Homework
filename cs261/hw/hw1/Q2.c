/*******************************************************************
** Name: Kevin Sliker, Vlad Predovic
** Date: 4-4-2015
** Solution description: Passes pointers/int to a function
** and returns the results after being manipulated.
** Visual Studio 2013
*******************************************************************/

#include <stdlib.h>
#include <stdio.h>

/*changes the value of the provided integer and pointers
preconditions:  2 int pointers and 1 pointer initialized with values
postconditions : changed values.*/
int foo(int *a, int *b, int c)
{
	//set a to double its original value
	*a = *a*2;

	//set b to half its original value
	*b = *b/2;

	//assign a+b to c
	c = *a + *b;

	//return c
	return c;

}



int main()
{
	//declare three integers x, y and z and initialize them to 7, 8, 9 respectively
	int x = 7;
	int y = 8;
	int z = 9;

	//print the values to x, y and z
	printf("x: %d   y: %d    z: %d\n", x, y, z);

	//call foo() appropriately, passing x,y,z as parameters
	int fooval = foo(&x, &y, z);

	//print the value returned by foo
	printf("foo returned: %d\n", fooval);	

	//print the values of x, y and z again
	printf("x: %d   y: %d    z: %d\n", x, y, z);

	return 0;
}
