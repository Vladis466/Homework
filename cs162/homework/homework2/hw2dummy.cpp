#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <istream>
#include <string>
#include <algorithm>


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
			
			cout << Num << " / " << Den << endl << endl << endl;
			
			for (int i = Den * Num; i > 1; i--) {  
                if ((Den % i == 0) && (Num % i == 0)) {  
				
				
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
	
	//This is the link which will tell the operator how to output the variables in the class.
	int Numerator = Fraction.Num;
	int Denominator = Fraction.Den;	

	output << "Your final reduced number is"  << Numerator << " / " << Denominator << endl;

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
 
int typeCheck (int& dummy, string Input){
//what kind of results we want add/mult/div/sub
		int spaceCheck = 0;
		for(int i = 0; i < Input.length(); i++){
			if(Input[i] == ' '){
				spaceCheck++;				
			}
			//Choose what we want to do mult sub add or div
			if(Input[i] == '+') {
				dummy = 1;
				
			} else if(Input[i] == ' ' && Input[i-1] == ' '){
				dummy = 2;
				
			} else if(Input[i] == '*'){
				dummy = 3;
			} else if(Input[i] == '/' && Input[i-4] == '/' && Input[i+4] == '/'){
				dummy = 4;
			}
			//cout << dummy << endl;	
		}
		
		return spaceCheck;

}


string Transformer(string Initial) {

	char chars[] = "-";

   for (unsigned int i = 0; i < strlen(chars); ++i)
   {
     
      Initial.erase (remove(Initial.begin(), Initial.end(), chars[i]), Initial.end());
   }


   cout << Initial << endl;
   
   return Initial;
}

int findNeg(string str, int lenInput){
	int numSwitch = 0;
	int i;
	if(lenInput = 2){
		if(str[0] == '-' ^ str[4] == '-'){
		numSwitch = 1;
		}
	}
	if(lenInput = 6){
		if(str[0] == '-' ^ str[4] == '-'){
		numSwitch = 1;
		}
		if(str[10] == '-' ^ str[15] == '-'){
		numSwitch = 2;
		}
		if(str[8] == '-' ^ str[12] == '-'){
		numSwitch = 2;
		}
		if((str[0] == '-' ^ str[4] == '-') && (str[9] == '-' ^ str[13] == '-')){
		numSwitch = 3;
		}
	
	}
	return numSwitch;
}	

int main() {
		int negSwitch = 0;
		int spaceCheck = 0;
		int dummy;
		
		cout << "You can input numbers in fraction form with spaces in between the characters." << endl;
		cout << "However, if a value is negative, do not leave a space between the character and the number" << endl;
		cout << "The format should look like this -----> -4 / 3 + 3 / -4" << endl;
		cout << "Also do not enter two negatives in a fraction because thats positive anyway thanks!" << endl;
		cout << "For the purpose of this program, single digit entries only(between 1 - 9)"<< endl << endl;
		 
		Rational Meow1;
		Rational Meow2;
	
		string Input;
		
		int Denum1, Numer1, Denum2, Numer2, numFin, denFin;
		cout << "Insert your cool fraction or arithmetic compound" << endl;
		getline(cin, Input);
		
		
		negSwitch = findNeg(Input, spaceCheck);
		
		
		//cout << spaceCheck << endl;
		//cout << dummy;
		Input = Transformer(Input);
		
		spaceCheck = typeCheck(dummy, Input);
		
		
		if (spaceCheck == 2){
			Numer1 = Input[0] - '0';
			Denum1 = Input[4] - '0';
			//Create Var
			if(Denum1==0){
				cout << "Oh my goz, u destroyed ze universe!!!" << endl;
				exit (EXIT_FAILURE);
			}
			
			if(negSwitch == 1){
				Numer1 = -Numer1;
			}
			Meow1.set_Values(Numer1, Denum1);
			
		} else if(spaceCheck == 6){
			cout << dummy << endl;
			if(dummy == 2){
				
			Numer1 = Input[0] - '0';
			Denum1 = Input[4] - '0';
			Numer2 = Input[7] - '0';
			Denum2 = Input[11] - '0';
			
			}else{
				
			Numer1 = Input[0] - '0';
			Denum1 = Input[4] - '0';
			Numer2 = Input[8] - '0';
			Denum2 = Input[12] - '0';
			}
			//Create var
			
			if(Denum1==0 || Denum2 == 0){
				cout << "Oh my goz, u destroyed ze universe!!!" << endl;
				exit (EXIT_FAILURE);
			}
			cout << negSwitch << endl;
			if(negSwitch == 1){
				Numer1 = -Numer1;
			}
			if(negSwitch == 2){
				Numer2 = -Numer2;
			}
			if(negSwitch == 3){
				Numer1 = -Numer1;
				Numer2 = -Numer2;
			}
			//cout << Numer1 << Denum1 << Numer2 << Denum2 << endl;
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



