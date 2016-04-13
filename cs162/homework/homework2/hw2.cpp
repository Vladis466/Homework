#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <istream>
#include <string>


using namespace std;


class Rational { 
	//our int vars that represent the denominator and numerator
	private:
		int Num, Den;

		
	public:
		//function definition for overloading as your best friend. 
		//MEET ALL MY FRIENDS
		friend std::ostream& operator <<(std::ostream& output, const Rational& Fraction);
		
		friend const Rational operator +(const Rational&, const Rational&);
		
		friend const Rational operator -(const Rational&, const Rational&);
		
		friend const Rational operator *(const Rational& First, const Rational& Second);
		
		friend const Rational operator /(const Rational& First, const Rational& Second);
		
		
		
		
		void Reduce() {
			//from the greatest common multiple until 2, cycle through each number
			//if both divided by a number give a remainder of 0, divide the values 
			// by this number (i), and repeat the process.
			cout << "Your starting value is" << endl;
	
			for (int i = Den * Num; i > 1; i--) {  
                if ((Den % i == 0) && (Num % i == 0)) {  
				
				cout << Num << " / " << Den << endl << endl << endl;
				Den = Den/i;  
                Num = Num/i;  
				
				}  
            }
		//cout << Num << " / " << Den << endl;
		}
			
		void set_Values(int, int);    //Constructor
};


//creating de the constructor(declaration). Wtf does this do...	
void Rational::set_Values(int Numerator, int Denominator) {
	//Tells us what members the class has so that we can declare variables of this type.
	cout << "Object created" << endl;
	Num = Numerator;
	Den = Denominator;
}

//Here we create what the overloaded left shift is going to, it's declaration.
std::ostream& operator<<(std::ostream& output, const Rational& Fraction) {
	
	int dummy = 0;
	//This is the link which will tell the operator how to output the variables in the class.
	int Numerator = Fraction.Num;
	int Denominator = Fraction.Den;
	cout << "If either the denominator or numerator BUT NOT BOTH are negative press 1" << endl;
	cout << "If both or neither are negative press 2" << endl;
	cin >> dummy;
	
	if (dummy == 1) {
	output << "Your final reduced number is" << " -" << Numerator << " / " << Denominator << endl;
	} else {
	output << "Your final reduced number is" << Numerator << " / " << Denominator << endl;
	}
	
	return output;
}

//All four of the operator overloads for arithmetic operations
const Rational operator +(const Rational& First, const Rational& Second) {
	Rational temp;
	temp.Num = First.Num * Second.Den + Second.Num * First.Den;
	temp.Den = Second.Den * First.Den;
	cout << endl << "THE VALUE of the summation IS HERE" << endl;
	return temp;
}

const Rational operator -(const Rational& First, const Rational& Second) {
	Rational temp;
	temp.Num = First.Num * Second.Den - Second.Num * First.Den;
	temp.Den = Second.Den * First.Den;
	cout << endl << "THE VALUE of the negation IS HERE" << endl;
	return temp;
}
 
const Rational operator *(const Rational& First, const Rational& Second) {
	Rational temp;
	temp.Num = First.Num * Second.Num;
	temp.Den = Second.Den * First.Den;
	cout << endl << "THE VALUE of the multiplication IS HERE" << endl;
	return temp;
}

const Rational operator /(const Rational& First, const Rational& Second) {
	Rational temp;
	temp.Num = First.Num * Second.Den;
	temp.Den = Second.Num * First.Den;
	cout << endl << "THE VALUE of the multiplication IS HERE" << endl;
	return temp;
}
 
int typeCheck (int& dummy){

}

int main() {
	
		int spaceCheck = 0;
		Rational Meow1;
		Rational Meow2;
	
		string Input;
		int Denum1, Numer1, Denum2, Numer2, numFin, denFin;
		cout << "Insert your cool fraction or arithmetic compound" << endl;
		getline(cin, Input);
		
		//what kind of results we want add/mult/div/sub
		int dummy;
		for(int i = 0; i < Input.length(); i++){
			if(Input[i] == ' '){
				spaceCheck++;				
			}
			//Choose what we want to do mult sub add or div
			if(Input[i] == '+') {
				dummy = 1;
				
			} else if(Input[i] == '-' && Input[i-1] == ' ' && Input[i+1] == ' '){
				dummy = 2;
				
			} else if(Input[i] == '*'){
				dummy = 3;
			} else if(Input[i] == '/' && Input[i-4] == '/' && Input[i+4] == '/'){
				dummy = 4;
			}
			//cout << dummy << endl;	
		}
		
		if (spaceCheck == 2){
			Numer1 = Input[0] - '0';
			Denum1 = Input[4] - '0';
			//Create Var
			Meow1.set_Values(Numer1, Denum1);
		} else if(spaceCheck == 6){
			Numer1 = Input[0] - '0';
			Denum1 = Input[4] - '0';
			Numer2 = Input[8] - '0';
			Denum2 = Input[12] - '0';	
			//Create var
			Meow1.set_Values(Numer1, Denum1);
			Meow2.set_Values(Numer2, Denum2);
			
			if(dummy == 1){
				Meow1 = Meow1 + Meow2;
			
			} else if(dummy == 2){
				Meow1 = Meow1 - Meow2;
				
			} else if(dummy == 3){
				Meow1 = Meow1 * Meow2;
				
			} else if(dummy == 4){
				Meow1 = Meow1 / Meow2;	
			}
		}
	

	//This function will reduce your fractions beastmode style.
	Meow1.Reduce();
	//This baby will output your fraction in it's FINAL FORM.
	cout << Meow1;
	
	return 0;
}

