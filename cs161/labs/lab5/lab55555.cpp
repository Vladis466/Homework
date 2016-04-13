#include <iostream>
#include <string> //string.h
#include <stdlib.h> //atoi and atof

using namespace std;

void function1(int);
void function2(int);
void function3(int,int);
void runagain();
bool is_positive_int(string);
bool is_positive_int_recurse(string input, int i);

int main() {
	string parameter;
	string parameter2;
			
	 bool loop = false;
		while( loop == false) {
			cout << "enter parameter please" << endl;
			cin >> parameter;
			

			cout << "enter new parameter" << endl;
			cin >> parameter2;
			
		if(is_positive_int_recurse(parameter, parameter.length())) {
			
			function1(atoi(parameter.c_str()));
			

			
			if(is_positive_int_recurse(parameter2, parameter2.length())) {
				function2(atoi(parameter2.c_str()));
				function3 (atoi(parameter.c_str()), atoi(parameter2.c_str()));
				runagain();
				
				loop = true;
			}
		} else {
			loop = false;
		}
	}
}

void function1 (int parameter) {
	for(int i = 0; i <= parameter; i++) {
		cout << i << endl;
	}
		cout << endl << endl << endl << endl;
}

void function2(int parameter) {
	for(int i = parameter; i >= 0; i--) {
		cout << i << endl;
	}
		cout << endl << endl << endl << endl;
}

void function3(int parameter1, int parameter2) {
	if ( parameter1 < parameter2) {
	
		for(int i = parameter1; i <= parameter2; i++ ) {
			
			cout << i << endl;
		}
	}  else if (parameter1 > parameter2) {
		for (int i = parameter1; i >= parameter2; i--) {
			cout << i << endl;
		}
	} else {
		cout << parameter1 << " = " << parameter2 << endl;
	}
}

void runagain() {
	cout << "would you like to run this function again or quit"<< endl;
	cout << "Press 1 for yes or 2 for no" << endl;
}

bool is_positive_int(string input) {
	bool error = false;
	for(int x = 0; x <input.length(); x++) {
		//if the character in the string is not between 0 and 1 in ASCII, quit program
		if((!(input.at(x) >= '0' && input.at(x) <= '9'))){
			error = true;
			break;
		}
	}
	if(error) {
		return false;
	} else {
		return true;
	}
}



bool is_positive_int_recurse(string numStr, int i) {
	if(numStr[i] == '-') {
		return false;
	} else if( i == 0 && numStr[i] > 48 && numStr[i] < 58) {
		return true;
	}

	return is_positive_int_recurse(numStr, --i);
}
