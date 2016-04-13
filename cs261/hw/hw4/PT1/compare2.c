#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "structs.h"


 
int compare2(TYPE left, TYPE right)
{
	struct monkey* data1;
	struct monkey* data2;
	data1 = (struct monkey*)left;				//casting, how does this work??
	data2 = (struct monkey*)right;

	if (data1->age < data2->age)
	{	
		return 1;
	}
	else if (data1->age > data2->age)
	{
		return -1;
	}
	else
	{
		return 0;
	}
	

}

/*Define this function, type casting the value of void * to the desired type*/
void print_type2(TYPE curval)
{
	assert(curval != 0);
	struct monkey *printer = (struct monkey*) curval;

	printf("%p", printer);
}


