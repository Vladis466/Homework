#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
	int perfy;
	int i, j;
	int Sums;
	printf("Insert number to to search up to for perfectitude \n");
	scanf ("%d",&perfy);
	i = 1;
	for(j = 2; j < perfy; j++)
	{	
		i = 1;
		Sums = 0;
		while(i < j)
		{
			if(j % i == 0)
				Sums += i;
			i++;
		}

	    if(Sums==j)
		    printf("%d is a perfect number\n",j);
	    else
		    printf("%d is not a perfect number\n",j);
	}
}

