#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynamicArray.h"


/* param: s the string
   param: num a pointer to double
   returns: true (1) if s is a number else 0 or false.
   postcondition: if it is a number, num will hold
   the value of the number
*/

void Allocate(double *num1, double *num2, struct DynArr *stack, int n)
{
	if (n == 1)
	{
		*num1 = topDynArr(stack);
		popDynArr(stack);
	}

	*num2 = topDynArr(stack);
	popDynArr(stack);

}

int isNumber(char *s, double *num)
{
	char *end;
	double returnNum;

	if(strcmp(s, "0") == 0)
	{
		*num = 0;
		return 1;
	}
	else 
	{
		returnNum = strtod(s, &end);
		/* If there's anything in end, it's bad */
		if((returnNum != 0.0) && (strcmp(end, "") == 0))
		{
			*num = returnNum;
			return 1;
		}
	}
	return 0;  //if got here, it was not a number
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their sum is pushed back onto the stack.
*/
void add (struct DynArr *stack)
{	

	double val1, val2;
	/*val1 = topDynArr(stack);
	popDynArr(stack);
	val2 = topDynArr(stack);
	popDynArr(stack);*/
	Allocate(&val2, &val1, stack, 1);
	val1 = val1 + val2;
	pushDynArr(stack, val1);


	val2 = topDynArr(stack);								//Used to check that this function is working correctly
	printf("value of add: %f \n", val2);					//By examining the top 2 values of the stack.

}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their difference is pushed back onto the stack.
*/
void subtract(struct DynArr *stack)
{
	double val1, val2;
	Allocate(&val2, &val1, stack, 1);
	popDynArr(stack);
	val1 = val1 - val2;
	pushDynArr(stack, val1);

	val2 = topDynArr(stack);								//Used to check that this function is working correctly
	printf("value of difference: %f \n", val2);					//By examining the top 2 values of the stack.
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their quotient is pushed back onto the stack.
*/
int divide(struct DynArr *stack)
{
	double val1, val2;
	Allocate(&val2, &val1, stack, 1);

	if (val2 == 0)
	{
		printf("Undefined value: You can't divide by zero\n. Program aborted");
		return 1;
	}
	else
	{
		val1 = val1 / val2;
		pushDynArr(stack, val1);

		val2 = topDynArr(stack);								//Used to check that this function is working correctly
		printf("value of division: %f \n", val2);					//By examining the top 2 values of the stack.
	}
	return 0;
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their quotient is pushed back onto the stack.
*/
void multiply(struct DynArr *stack)
{
	double val1, val2;
	Allocate(&val2, &val1, stack, 1);

	val1 = val1 * val2;
	pushDynArr(stack, val1);

	val2 = topDynArr(stack);								//Used to check that this function is working correctly
	printf("value of multiplication: %f \n", val2);					//By examining the top 2 values of the stack.
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their quotient is pushed back onto the stack.
*/
void power(struct DynArr *stack)
{
	double val1, val2;
	Allocate(&val2, &val1, stack, 1);

	val1 = pow(val1, val2);
	pushDynArr(stack, val1);
	
	val2 = topDynArr(stack);								//Used to check that this function is working correctly
	printf("value of power: %f \n", val2);					//By examining the top 2 values of the stack.
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their quotient is pushed back onto the stack.
*/
void squared(struct DynArr *stack)
{
	double val1, val2;
	Allocate(&val2, &val1, stack, 0);

	val1 = val1 * val1;
	pushDynArr(stack, val1);

	val2 = topDynArr(stack);								//Used to check that this function is working correctly
	printf("value of square: %f \n", val2);					//By examining the top 2 values of the stack.
}


/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their quotient is pushed back onto the stack.
*/
void cubed(struct DynArr *stack)
{
	double val1, val2;
	Allocate(&val2, &val1, stack, 0);

	val1 = val1 * val1 * val1;
	pushDynArr(stack, val1);

	val2 = topDynArr(stack);								//Used to check that this function is working correctly
	printf("value of cube: %f \n", val2);					//By examining the top 2 values of the stack.
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their quotient is pushed back onto the stack.
*/
void absVal(struct DynArr *stack)
{
	double val1, val2;
	Allocate(&val2, &val1, stack, 0);

	val1 = fabs(val1);
	pushDynArr(stack, val1);

	val2 = topDynArr(stack);								//Used to check that this function is working correctly
	printf("absolute value of input: %f \n", val2);			//By examining the top 2 values of the stack.
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their quotient is pushed back onto the stack.
*/
int Sqroot(struct DynArr *stack)
{
	double val1, val2;
	Allocate(&val2, &val1, stack, 0);
	if (val1 < 0)
	{
		printf("Cannot take the square root of a negative number, Mission aborted. \n");
		return 1;
	}
	else
	{
	val1 = sqrt(val1);
	pushDynArr(stack, val1);

	val2 = topDynArr(stack);								//Used to check that this function is working correctly
	printf("the square root is: %f \n", val2);			//By examining the top 2 values of the stack.
	}
	return 0;
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their quotient is pushed back onto the stack.
*/
void Exponential(struct DynArr *stack)
{
	double val1, val2;
	Allocate(&val2, &val1, stack, 0);

	val1 = exp(val1);
	pushDynArr(stack, val1);

	val2 = topDynArr(stack);								//Used to check that this function is working correctly
	printf("the exponential value is: %f \n", val2);			//By examining the top 2 values of the stack.
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their quotient is pushed back onto the stack.
*/
void nattyLog(struct DynArr *stack)
{
	double val1, val2;
	Allocate(&val2, &val1, stack, 0);

	val1 = log(val1); 
	pushDynArr(stack, val1);

	val2 = topDynArr(stack);								//Used to check that this function is working correctly
	printf("natural log of input: %f \n", val2);			//By examining the top 2 values of the stack.
}

void b10Log(struct DynArr *stack)
{
	double val1, val2;
	Allocate(&val2, &val1, stack, 0);

	val1 = log10(val1);
	pushDynArr(stack, val1);

	val2 = topDynArr(stack);								//Used to check that this function is working correctly
	printf("log base 10 of input: %f \n", val2);			//By examining the top 2 values of the stack.
}



double calculate(int numInputTokens, char **inputString)
{
	int i, Error, Exiter;
	double result = 0.0;
	char *s;
	struct DynArr *stack;
	double num;
	//set up the stack
	stack = createDynArr(20);

	// start at 1 to skip the name of the calculator calc
	for(i=1;i < numInputTokens;i++) 
	{
		s = inputString[i];
		printf("input %s \n", s, inputString[i]);



		// Hint: General algorithm:
		// (1) Check if the string s is in the list of operators.
		//   (1a) If it is, perform corresponding operations.
		//   (1b) Otherwise, check if s is a number.
		//     (1b - I) If s is not a number, produce an error.
		//     (1b - II) If s is a number, push it onto the stack

		if (strcmp(s, "+") == 0)
		{
			if (sizeDynArr(stack) != 2)
			{
				printf("Too few or too many arguments");
				exit(EXIT_FAILURE);
			}
			add(stack);
		}
		else if (strcmp(s, "-") == 0)
		{
			if (sizeDynArr(stack) != 2)
			{
				printf("Too few or too many arguments");
				exit(EXIT_FAILURE);
			}
			subtract(stack);
		}
		else if (strcmp(s, "/") == 0)
		{
			if (sizeDynArr(stack) != 2)
			{
				printf("Too few or too many arguments");
				exit(EXIT_FAILURE);
			}
			Exiter = divide(stack);
			if (Exiter == 1){
				exit(EXIT_FAILURE);
			}
		}
		else if (strcmp(s, "x") == 0)
		{
			if (sizeDynArr(stack) != 2)
			{
				printf("Too few or too many arguments");
				exit(EXIT_FAILURE);
			}
			multiply(stack);
		}
		else if (strcmp(s, "^") == 0)
		{
			if (sizeDynArr(stack) != 2)
			{
				printf("Too few or too many arguments");
				exit(EXIT_FAILURE);
			}
			power(stack);
		}
		else if (strcmp(s, "^2") == 0)
		{
			if (sizeDynArr(stack) != 1)
			{
				printf("Too few or too many arguments");
				exit(EXIT_FAILURE);
			}
			squared(stack);
		}
		else if (strcmp(s, "^3") == 0)
		{
			if (sizeDynArr(stack) != 1)
			{
				printf("Too few or too many arguments");
				exit(EXIT_FAILURE);
			}
			cubed(stack);
		}
		else if (strcmp(s, "abs") == 0)
		{
			if (sizeDynArr(stack) != 1)
			{
				printf("Too few or too many arguments");
				exit(EXIT_FAILURE);
			}
			absVal(stack);
		}
		else if (strcmp(s, "sqrt") == 0)
		{
			if (sizeDynArr(stack) != 1)
			{
				printf("Too few or too many arguments");
				exit(EXIT_FAILURE);
			}
			Exiter = Sqroot(stack);
			if (Exiter == 1){
				exit(EXIT_FAILURE);
			}
		}
		else if (strcmp(s, "exp") == 0)
		{
			if (sizeDynArr(stack) != 1)
			{
				printf("Too few or too many arguments");
				exit(EXIT_FAILURE);
			}
			Exponential(stack);
		}
		else if (strcmp(s, "ln") == 0)
		{
			if (sizeDynArr(stack) != 1)
			{
				printf("Too few or too many arguments");
				exit(EXIT_FAILURE);
			}
			nattyLog(stack);
		}
		else if (strcmp(s, "log") == 0)
		{
			if (sizeDynArr(stack) != 1)
			{
				printf("Too few or too many arguments");
				exit(EXIT_FAILURE);
			}
			b10Log(stack);
		}
		else 
		{

			if (s == "pi")
			{
				s = "3.14";
				printf("pi computed\n");
			}
			if (s == "e")
			{
				s = "2.72";
				printf("e computed\n");
			}
			Error = isNumber(s, &num);
			if (Error == 0)
			{
				printf("ERROR WRONG INPUT");
				exit(EXIT_FAILURE);
			}
			//printf("num: %f\n", num);							//used to check output number working
			pushDynArr(stack, num);
			
			
			// FIXME: You need to develop the code here (when s is not an operator)
			// Remember to deal with special values ("pi" and "e")
			
		}
	}	//end for 

	/* FIXME: You will write this part of the function (2 steps below) 
	 * (1) Check if everything looks OK and produce an error if needed.
	 * (2) Store the final value in result and print it out.
	 */
	result = topDynArr(stack);
	deleteDynArr(stack);

	printf("the final result: %f \n", result);
	return result;
}

int main(int argc , char** argv)
{
	// assume each argument is contained in the argv array
	// argc-1 determines the number of operands + operators
	if (argc == 1)
		return 0;

	calculate(argc,argv);
	return 0;
}
