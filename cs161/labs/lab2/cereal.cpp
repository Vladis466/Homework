#include <iostream>
int main() {
/* weight of package of breakfastcereal in ounces*/
int weight
/* expected user lifespan in years */
int life
/* number of boxes of cereal eaten in week */
int boxes
/* ton in ounces */
int ton
ton = 35273.92
cout << "Enter weight of cereal in ounces\n" << endl;
cin >> weight;
cout << "Enter expected life span\n" << endl;
cin >> life;
cout << "Enter boxes of cereal eaten in week"  
cin >> ton;

/*return weight of  package of cereal in tons */
double toncerealbox
toncerealbox = weight / ton 
/* return boxes needed to yield one metric ton */
double boxesinaton
boxesinaton = (ton / toncerealbox)
/* number of boxes eaten by user in a lifetime */
double cereallife
cereallife = (life * 52 * boxes)
cout << "The number of boxes eaten in a lifetime is\n" cereallife <

