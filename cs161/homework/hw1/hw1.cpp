/***********************
 ** program: hw1.cpp
 ** Author: Vlad Predovic
 ** Date: 10/10/2014
 ** Description:
 ** Input: test averages for 5 seperate tests
 ** Output: test average for 5 scores in decimal binary hexadecimal and octal forms
************************/
 
#include <iostream>
#include <limits.h>
#include <math.h>
#include <iomanip>

using namespace std;

int main() {

	cout << endl;

	cout << "Min value for unsigned is 0" << endl; 
	cout << "Max value for unsigned" << ULLONG_MAX << endl;
	cout << "Min value for signed" << LLONG_MIN << endl;
	cout << "Max value for signed" << LLONG_MAX << endl;

short int smallshort = SHRT_MIN;
short int largeshort = SHRT_MAX;
short int usmallshort = 0;
short int ulargeshort = USHRT_MAX;
int usmallint = 0;
int ulargeint = UINT_MAX;
int smallint = INT_MIN;
int largeint = INT_MAX;
long int smalllong = LONG_MIN;
long int largelong = LONG_MAX;
long int usmalllong = 0;
long int ulargelong = ULONG_MAX;

	cout << endl;

	cout << "Size of short, int and long, signed and then unsigned" << endl;
/*First the largest and smallest signed values. the smallest shorts are negative and
**you do not subtract 1 because negatives begin at 1 since 0 is considered positive	
*/
	cout << endl;
	cout << " largest short signed " << pow(2,sizeof(short)*8-1)-1 << endl;
	cout << " largest int signed " << pow(2,sizeof(int)*8-1)-1 << endl;
	cout << " largest long signed " << pow(2,sizeof(long)*8-1)-1 << endl;
	cout << " smallest short signed " <<-(pow(2,sizeof(short)*8-1)) << endl;
	cout << " smallest int signed " << -(pow(2,sizeof(int)*8-1)) << endl;
	cout << " smallest long signed " << -(pow(2,sizeof(long)*8-1)) << endl;

//Then the largest and smallest unsigned values. The -1 on the inside of the parenthesis  
//was removed because unsigned take the full value of possibilities since its all positive
	cout << endl;

	cout << " largest short unsigned " << pow(2,sizeof(short)*8)-1 << endl;
	cout << " largest int unsigned " << pow(2,sizeof(int)*8)-1 << endl;
	cout << " largest long unsigned " << pow(2,sizeof(long)*8)-1 << endl;
	cout << " smallest short unsigned " << 0 << endl;
	cout << " smallest int unsigned " << 0 << endl;
	cout << " smallest long unsigned " << 0 << endl;

	cout << endl;

// declare five variables that will be test prompted test scored 
	double x1, x2, x3, x4, x5;

/* prompt user for test sores */
	cout <<  "Insert five test scores" << endl;
	cin >> x1;
	cin >> x2;
	cin >> x3;
	cin >> x4;
	cin >> x5;

/* declare variable and set to average of 5 test scores selected*/
int testavg = (x1 + x2 + x3 + x4 + x5)/5; 	
	cout << "Your average test score is " << round(testavg) << fixed << std::setprecision(1) << endl;
	cout << " as a rounded whole number in decimal " << round(testavg) << endl;

	cout << endl;

//The hex reference sets the base of the number selected to octal
	cout << " in hexadecimal form: " << hex << testavg << endl;

	cout << endl;

//The oct reference sets the base of the number selected to octal
	cout << " In octal decimal form " << oct << testavg << endl;

	cout << endl;

	cout << " test average in binary form below" << endl;

	cout << endl;
/*In order to do this I rounded down on the value to be subtracted if the test average was
**below 1 because it meant that you had to put a 0 in the binary code at that spot and move 
** down to the next bit.
*/

	cout << testavg/(short)pow(2,7) << endl;
	testavg = testavg - floor(testavg/pow(2,7))*pow(2,7);
	cout << testavg/(short)pow(2,6) << endl;
	testavg = testavg - floor(testavg/pow(2,6))*pow(2,6);
	cout << testavg/(short)pow(2,5) << endl;
	testavg = testavg - floor(testavg/pow(2,5))*pow(2,5);
	cout << testavg/(short)pow(2,4) << endl;
	testavg = testavg - floor(testavg/pow(2,4))*pow(2,4);
	cout << testavg/(short)pow(2,3) << endl;
	testavg = testavg - floor(testavg/pow(2,3))*pow(2,3);
	cout << testavg/(short)pow(2,2) << endl;
	testavg = testavg - floor(testavg/pow(2,2))*pow(2,2);
	cout << testavg/(short)pow(2,1) << endl;
	testavg = testavg - floor(testavg/pow(2,1))*pow(2,1);
	cout << testavg/(short)pow(2,0) << endl;
	testavg = testavg - floor(testavg/pow(2,0))*pow(2,0);

		
	cout << " Thank you for using the program. Send any feedback to predoviv@onid.oregonstate.edu" << endl;
	cout << endl;

	cout << "(╯°□°）╯︵ ┻━┻" << endl;
	cout << "(•_•) / ( •_•)>⌐■-■ / (⌐■_■)" << endl;
	cout << "This program has been......flipped ~~" << endl;
}
