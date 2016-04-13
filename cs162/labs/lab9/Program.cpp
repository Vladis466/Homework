#include <iostream>
#include <stdlib.h>
#include "FibonacciR.h"
#include "FibonacciNR.h"

//Includes required for the clock
#include <stdio.h>
#include <time.h>
#include <math.h>


using namespace std;
void Usage(){
 	cout<<"Correct Usage:"<<endl;
 	cout<<"./Fibonacci [n]"<<endl;
}
int main(int argc, char** args) {
	
	int startTimeR = clock()/CLOCKS_PER_SEC;  //  Start time for Recursive
	
	try{
 		const char* input; //Note: char by default initializes to '\0'
		if(args[1]!=0)
  		{
			cout<<"1st passed arguement: '"<<args[1]<<"'"<<endl;
			input= args[1];
 		}
		int n= atoi(input);
		cout<<"Finding '"<<n<<"'th "<<"fibonacci number...."<<endl;
		cout<<"Calling Recursive Fibonacci implementation"<<endl;
		FibonacciR fr(n);
		fr.PrintFibonacci();
		
		int endTimeR = (clock()/CLOCKS_PER_SEC) - startTimeR;  //  End Time for Recursive
		cout << "It took " << endTimeR << "seconds for the Recursive function" << endl;
		
		int startTimeNR = clock()/CLOCKS_PER_SEC;  //  Start time for Non-Recursive
		
		cout<<"Calling Non-Recursive Fibonacci implementation"<<endl;
		FibonacciNR fnr(n);
		fnr.PrintFibonacci();
		
		int endTimeNR = (clock()/CLOCKS_PER_SEC) - startTimeNR;  //  End Time for Recursive
		cout << "It took " << endTimeNR << "seconds for the Non-Recursive function" << endl;

		cout << "Done!!!!" << endl;
		return 0;
	}
   	catch(...)
   	{
		cout<<"Oops an error occured! Please check usage"<<endl;
		Usage();
		return 1;
	}
}