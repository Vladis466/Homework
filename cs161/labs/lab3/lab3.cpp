#include <iostream>
using namespace std;

int main() {

	double sweetmouse, weightmouse, goalweight, lifeyrs, canssodaperweek;
	
	double sodapoison = 0.001;
	
	cout << "Please input the amount of sweetener to kill a mouse: ";
	cin >> sweetmouse;
	cout << endl;
	
	
	cout << "Please input the weight of the mouse in lbs: ";
	cin >> weightmouse;
	cout << endl;
	
	
	cout << "Please input your goal weight in lbs: " << endl;
	cin >> goalweight;
	cout << endl;
	
	
	cout << "Please input how long you will live in years: " << endl;
	cin >> lifeyrs;
	cout << endl;
	
	
	cout << "Please input the amount of cans of diet soda you drink in a week: " <<endl;
	cin >> canssodaperweek;
	cout << endl;

	// amount of posion in body on ounces	
	double finalvalue = ((12 * canssodaperweek * lifeyrs * 52 * sodapoison)/goalweight);
	
	cout << "The amount of sweetener needed to kill you is: " <<  (sweetmouse*goalweight)/weightmouse << endl;
	cout << "The amount of sweetener you will consume in your lifetime is: " << finalvalue << endl;
	
	if ( finalvalue >= (sweetmouse/weightmouse)*goalweight) {
			cout << "You are going to die" << endl;
	
}   else   {  
			cout << "Bottoms up!" << endl;
}
	
	return 0;
}