/****************************************************************************
** Name: Vlad Predovic
** Date: 4-9-2015
** Solution description: Randomly creates scores and unique ID's for students.
** Then displays them in order of increasing score.
** Visual Studio 2013
****************************************************************************/

#include <stdlib.h>
#include <stdio.h>

struct student
{
	int id;
	int score;
};


/* put the students and their scores in ascending order 
preconditions:  student point array, size
postconditions : none.*/
void sort(struct student* students, int n)
{

	int temp;
	int x;
	int b;

	/*Sort the given array of students by score*/
	for (b = 0; b < 10; b++){
		for (int i = 0; i < n; i++){
			x = i;
			/*Here we compare the one score versus all others in the list*/
			while (i < 20){
				if (i == 19){
					break;
				}
				if (students[i].score > students[i + 1].score){
					temp = students[i + 1].score;
					students[i + 1].score = students[i].score;
					students[i].score = temp;

					temp = students[i + 1].id;               /*We have to do this to make sure the ID stays with the correct score*/
					students[i + 1].id = students[i].id;
					students[i].id = temp;
				}
				i++;
			}
			/*reusing variables :D*/
			i = x;
		}
	}

}

/*generate ID's and scores for the students, using rand()
preconditions:  student point array, size
postconditions : none.*/
void generate(struct student *students, int n)
{
	int i;
	int j;
	/*get a different set of random numbers every time rand is called*/
	srand(time(NULL));
	
	/*populate struct with random numbers */
	for(i = 0; i < n; i++)
	{
		students[i].id =rand() % 20;
		/*make sure id's are unique!!!*/
		for (j = 0; j < i; j++)
		{
			if (students[i].id == students[j].id)
			{
				i--;
			}
		}

		students[i].score = rand() % 100;
	}
}


/* Prints out ID and score of each student
preconditions:  student point array, size
postconditions : none.*/
void output(struct student *students, int n)
{
	int i;

	for(i = 0; i < n; i++)
	{
		printf("ID: %d    SCORE: %d\n", students[i].id, students[i].score);
	}

}

int main()
{
	//declare an integer n and assign it a value
	int n = 20;

	//allocate memory for n students using malloc
	struct student *students;
	students = (struct student *)malloc(n * sizeof(struct student));

	//generate random ID's and scores for the n students, using rand()
	generate(students, n);
	
	//print the contents of the array of n students
	output(students, n);

	//pass this array along with n to the sort() function
	sort(students, n);

	//print the contents of the array of n students
	printf("This is the array of students after being sorted:\n");
	output(students, n);


	return 0;
}
