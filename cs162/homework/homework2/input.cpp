#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <string>

using namespace std;


/* Design a program that will seperate an input
into different values for numerator and
the denominator form: 3 / 4 + 4 / 3
*/
main(){
	int spaceCheck = 0;
	
	string Input;
	int Denum1, Numer1, Denum2, Numer2, numFin, denFin;
	cout << "Insert your cool fraction or arithmetic compound" << endl;
	getline(cin, Input);
	
	for(int i = 0; i < Input.length(); i++){
		if(Input[i] == ' '){
			spaceCheck++;
			
		}
	}
	
	if (spaceCheck == 2){
		numFin = Input[0] - '0';
		denFin = Input[4] - '0';
	} else if(spaceCheck == 6){
		Numer1 = Input[0] - '0';
		Denum1 = Input[4] - '0';
		Numer2 = Input[8] - '0';
		Denum2 = Input[12] - '0';
		
		//Final Denominator
		denFin = Denum1 * Denum2;
		//Final Numerator
		numFin =  (Numer2 * Denum1) + (Numer1 * Denum2);
		
	}
	
		
		
	cout << denFin << endl;
	cout << numFin << endl;
	cout << spaceCheck << endl;
	cout << Input.size() << endl;
//	return 0;
}