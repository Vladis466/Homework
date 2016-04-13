#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace std;

long rfactorial (int n)	{	
	if	(n	==	1){	
			return	1;	
		}else{	
			return	n * rfactorial(n-1);	//	*	is	a	pending	
		}
}	

long	factorialHelper	(int	n,	int	result)	{	
	if	(n	==	1){
		return	result;	
	} else {	
		return	factorialHelper(n-1,n*result);
	}
}	

long	factorial(int	n)	{	
	return	factorialHelper(n,1);	
}	


int main() {
	int f;
	int tail;
	int rec;
	cout << "Ent a number" << endl;
	cin >> f;
	int startTimeR = clock(); 
	rec = rfactorial(f);
	int endTimeR = (clock()) - startTimeR; 
	
	int startTimeRtail = clock();
	tail =factorial(f);
	int endTimeRtail = (clock()) - startTimeRtail; 
	
	cout << "recursive value " << rec << " time: " << endTimeR<< endl;
	
	cout << "Tail recursive value " << tail << " time: " << endTimeRtail<< endl;
	return 0;
}

