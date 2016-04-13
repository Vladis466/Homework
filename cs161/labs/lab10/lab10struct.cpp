#include <iostream>
#include <string>

using namespace std;

struct vehicleParts {
  string wheels, doors, name;
  int power; //in horsepower
} bmw, volvo, mitsubishi;



int main() {

	bmw.wheels = "Michelin s3xx";
	bmw.doors = "4ffz3";
	bmw.power = 300;
	bmw.name = "330i";

	volvo.wheels = "Roadrunners9000";
	volvo.doors = "volvs63";
	volvo.power = 240;
	volvo.name = "S60";

	mitsubishi.wheels = "MeowphaltMunchers";
	mitsubishi.doors = "FlappyWings";
	mitsubishi.power = 180;
	mitsubishi.name = "Eclipse";

	cout << mitsubishi.wheels << mitsubishi.doors << mitsubishi.power << mitsubishi.name << endl;
	cout << volvo.wheels << volvo.doors << volvo.power << volvo.name << endl;
	cout << bmw.wheels << bmw.doors << bmw.power << bmw.name << endl;
return 0;
}