#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

float integrate_rectangle(float start, float finish, float iterations)
{
	float fx1, A;
	float sum = 0;
    float width=(finish-start)/iterations;
	for (float i=start;i<finish;i+=width) {
		fx1=pow(i,5)+10;
		A=fx1*width;
		sum=sum+A;
	}
	
	cout << sum << endl;
	return 0;
}

/* Alsaedi and Alaukaily*/
double Trap(double start, double end, int num)
{
   double sum=0.0;
   double A; // this is the area
   double width=(end-start)/num;
   double fx1,fx2;
   for (double i=start;i<end;i+=width)
   {
      fx1=pow(i,5.0)+10.0;
      fx2=pow((i+width),5.0)+10.0;
      A=((fx1+fx2)/2)*width;
      sum=sum+A;
   }
   cout << sum << endl;
   return(sum);
}

int f(float x) {
	return (pow(x, 5) + 10);
}

void summation(float end_point) {
	int sum = 0;
	for (int x = 1; x <= end_point; x++) {
		sum = sum + f(x);
	}
	cout << "The result of summation is: " << sum << endl;	
}

float creator(string msg) {
	bool dummy = false;	
	string in;
	while(dummy == false) {
	dummy = true;
	cout << "Please Input " << msg << endl;
	getline(cin, in);
		
		for(int a = 0 ; a < in.length() ; a++){	
			/*This code is to cycle through each index of each array input looking for a non-numeric input*/
			if (isdigit(in[a]) == false){		
				cout << "Input is not a valid number, please try again"<< endl;				
				dummy = false;
				break;
				} 
			
		}
	
	}
	return atof(in.c_str() );
}	

int main() {

	float end_point = creator("end_point");
	float start_point = creator("start_point");
	int	iterations = creator("iterations");

	cout << "Which operation would you want to do" << endl;
	cout << "1 for summation, 2 for integration" << endl;
	int choice;
	cin >> choice;
	if (choice == 1) {
		summation(end_point);
	}
	else if (choice == 2) { //run integration method
	
		cout << "How would you like to calculate the area??" << endl;
		cout << "1 for rectangle, 2 for trapezoid, 3 for both methods" << endl;
		int choiceArea;
		cin >> choiceArea;
		
		if (choiceArea == 1) {
			integrate_rectangle(start_point, end_point, iterations);
		}
		else if (choiceArea == 2) {
			
			Trap(start_point, end_point, iterations);
		}
		else if (choiceArea == 3) {
			Trap(start_point, end_point, iterations);
			integrate_rectangle(start_point, end_point, iterations);
		}
		else {
			cout << "Invalid input sir..." << endl;
			exit(0);
		}
		
	}
	else {cout << "stupid..." << endl; exit(0);}
	

	
	 
	return 0;
}







