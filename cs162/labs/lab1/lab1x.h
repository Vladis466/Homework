#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

struct mult_div_values{
		int mult;
		float div;
};

mult_div_values** create_table(int, int);

void set_mult_values(mult_div_values **table, int m, int n);

void set_div_values(mult_div_values **table, int m, int n);

void printarray(int m, int n, mult_div_values **table);

float Amt_Range(string &amount, string msg); 

bool digCheck(string str);

float numCheckfin(float score,bool& dum );