#include <iostream>
#include <math.h>
//Defines the specific weight of water
#define WATER_WEIGHT 62.4
using std::cout;
using std::cin;
using std::endl;

int main() {
	 //Variables needed to calculate buoyancy
	 float radius, bforce, volume,weight;
	 //Prompt user for weight and radius of sphere
	 cout << "Please enter the weight (lbs): " << endl;
	 cin >> weight;
	 cout << "Please enter the radius: " << endl;
	 cin >> radius;
	 //Calculate the volume and buoyancy force
	 volume = 4/3 * M_PI * pow(radius, 3);
	 bforce = volume * WATER_WEIGHT;
	 //Determine if the sphere will sink or float
	 if(bforce >= weight) {
	 cout << "The sphere will float!\n";
	 }  else  {
	 cout << "The sphere will sink!\n";
	 }
	 return 0;
 }
