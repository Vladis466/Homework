/*********************************************************************
** Name: Kevin Sliker, Vlad Predovic
** Date: 4-4-2015
** Solution description: Create and output a list of 10 students with 
** their unique ID's and scores, the max, the min, and the average score.
** Visual Studio 2013
*********************************************************************/


#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

struct student
{
	int id;
	int score;
};

/*Creates an array,allocating memory for 10 students and initializing to 0.
preconditions: set result equal to this in main
postconditions: initialized array.*/
struct student *allocate()
{
	/*allocate memory for ten students*/
	struct student *student_array;
	student_array = (struct student *) calloc(20, sizeof(int*));
	/*return the pointer*/
	return student_array;
}


/*generate random ID and score for 10 students, ID being between 1 and 10, scores between 0 and 100*/
void generate(struct student *students)
{
	int i, j;
	
	/*get a different set of random numbers every time rand is called*/
	srand(time(NULL));

	/*populate struct with random numbers*/
	for(i = 0; i < 10; i++)
	{
		students[i].id = 1 + rand() % 10;
		/*make sure id's are unique*/
		for (j = 0; j < i; j++)
		{
			if (students[i].id == students[j].id){
				i--;
			}
		}
		students[i].score = rand() % 100;
		
	}
}

/*output information about the ten students in this format*/
/*
	ID1 Score1
	ID2 Score2
	.
	.
	.
*/

/*Prints values for each student(ID and score).
preconditions: the filled student array
postconditions: none.*/
void output(struct student *students)
{
	int i;

	for(i = 0; i < 10; i++)
	{
		printf("ID%d: %d Score%d:  %d\n", i, students[i].id, i, students[i].score);
	}

}


/*compute and print the minimum, maximum and average scores of the ten students
preconditions:  the filled student array
postconditions: none.*/
void summary(struct student* students)
{
	int min, max, avg, i;

	/*compute min*/
	min = 100;
	for(i = 0; i < 10; i++)
	{
		if(min > students[i].score)
		{
			min = students[i].score;
		}
	}
	/*print min*/
	printf("The min score was: %d\n", min);


	/*compute max*/
	max = 0;
	for(i = 0; i < 10; i++)
	{
		if(max < students[i].score)
		{
			max = students[i].score;
		}
	}
	/*print max*/
	printf("The max score was: %d\n", max);


	/*compute avg*/
	avg = 0;
	for(i = 0; i < 10; i++)
	{
		avg += students[i].score;
	}
	avg = avg / 10;

	/*print avg*/
	printf("The average score was: %d\n", avg);

}


/*deallocate memory from stud
preconditions:  the filled student array
postconditions : free memory.*/
void deallocate(struct student *stud)
{
	if(stud != NULL)
	{
		free(stud);
	}

}



int main()
{
	struct student *stud = NULL;

	/*call allocate*/
	stud = allocate();
	/*call generate*/
	generate(stud);	
	/*call output*/
	output(stud);	
	/*call summary*/
	summary(stud);
	/*call deallocate*/
	deallocate(stud);
	return 0;
}
