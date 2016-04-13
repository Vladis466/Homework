#include <iostream>
#include <string>
//#include <cstring>
#include <cstdlib>

using namespace std;

/* this function counts up from 0
until it meets the number that's the first parameter
The only parameter is x, which is the first user input
It doesn't return anything to main
pre-condition: x is a positive integer
post-condition: x is unchanged */

void countUp (int x) {
	for(int i = 0; i <= x; i++) {
		cout << i << " ";
	}
	cout << endl;
	//return x;
}

/* this function counts down to 0
starting from the number specified in the second parameter
The only parameter is y, which is the second user input
It doesn't return anything to main
Pre-condition: y is a positive int
Post-condition: y is unchanged */

void countDown (int y) {
	//int i = y
	for(int i = y; i >= 0; i--) {
		cout << i << " ";
	}
	
	cout << endl;
	//return y;
}

/* This function counts in between
 * the two user-defined parameters
 * The inputs are x and y (first and second parameter)
 * from the user
 * It doesn't return anything to main
 * Pre-condition: y and x are positive ints
 * Post-condition: y and x are unchanged */
void countBtwn (int x, int y) {
	if (x < y) {
		for(int a = x; a <= y; a++)
		   	cout << a << " ";
		cout << endl;
	} else if (x > y) {
	   	for(int a = x; a >= y; a--)
			cout << a << " ";
		cout << endl;
	} else
	   cout << "The two parameters are equal!" << endl;
}

/* This function calls all the functions in order
 * and tells the user what is going on
 * The inputs are the functions countUp, countDown, and countBtwn
 * each with their variables, x and y
 * It doesn't return anything to main
 * Pre-conditions: x and y are positive ints
 * 		  the functions have positive outputs
 * Post-conditions: x and y are unchanged */
void get (int x, int y) {
   	cout << "Count up" << endl;
	countUp(x);
	cout << "Count down" << endl;	
	countDown(y);
	cout << "Count between" << endl;
	countBtwn(x, y);

}

/* This function error checks to make sure all the numbers entered are positive ints
 * The inputs are the two user-entered paramters in strings
 * outputs are the two parameters in ints, as long as they were entered correctly
 * pre-conditions are anything, as this is the error checking function
 * post-conditions are that x and y are for sure positive ints */
/*void is_positive_int(string xStr, string yStr, int x, int y) {
   int i = 0;
   	while (i < xStr.length() || i < yStr.length()) {
	   if ((xStr.at(i) < '0') || (yStr.at(i) < '0') || (xStr.at(i) > '9') || (yStr.at(i) > '9')) {
		cout << "You didn't enter a positive int... Please enter both again: ";
		cin >> xStr;
		cin >> yStr;
		i = 0;
	   } else i++;
	}
	x = atoi(xStr.c_str());
	y = atoi(yStr.c_str());
}*/

bool is_positive_int_recurse(string numStr, int i) {
	if(numStr[i] == '-') {
		return false;
	} else if( i == 0 && numStr[i] > 48 && numStr[i] < 58) {
		return true;
	}

	return is_positive_int_recurse(numStr, --i)
}



/* Defines the variables and asks for the user input
 * also calls get() and can restart the program based on user input
 * variables: x, y, return
 * Pre-conditions: x and y are positive ints
 * 		   the user inputs only a 1 or 0 for restarting
 * Post-conditions: arguments are the same */
int main () {
   	int x, y, a, i, restart;
	string xStr, yStr;
	cout << "Please enter 2 positive ints" << endl;
	cin >> x >> y;
	a = x;
	while (true) {
		if(is_positive_int_recurse(a, a.length())){
			get(x, y);
			break;
		}
		else {
	 	  	cout << "Did not enter a valid num. Try again.";
		}
	}	
	cout << "Run this again with different ints? 1 for yes, 2 for no" << endl;
	cin >> restart;
	if (restart == 1) main();
	return 0;
}
