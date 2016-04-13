// unit test for compare()

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
	int a[] = {5, 3, 90};
	int b[] = {3, 5, 90};
	int result;
	FILE *fp;

	fp = fopen("unittestresults.out", "w");
	fprintf(fp, "unittest1 for compare(): ");
	

	if ((result = compare((void*) &a[0], (void*) &b[0])) != 1) { // failure
		fprintf(fp, "expected %d (a > b), found %d\n", 1, result);
	} else if ((result = compare((void*) &a[1] , (void*) &b[1])) != -1) { // failure
		fprintf(fp, "expected %d (a < b), found %d\n", -1, result);
	} else if ((result = compare((void*) &a[2], (void*) &b[2])) != 0) { // failure
		fprintf(fp, "expected %d (a == b), found %d\n", 0, result);
	} else { // success
		fprintf(fp, "success\n");
	}
	
	fclose(fp);
	return 0;
}
