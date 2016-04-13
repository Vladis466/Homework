/***********************
 ** program: hw6.cpp
 ** Author: Vlad Predovic
 ** Date: 10/23/2014
 ** Description: Creates a randomized 2 array of a size of your choosing. Then creates an
 ** array of n-1 size whose components are the sum of your arrays. Using a matrix structure!
 ** Input: array size, whether to run the program recursively or not, and a number.
 ** Output: a 2d matrix of size n-1 /w cool inputs
************************/

#include <iostream>
#include <stdlib.h>

using namespace std;


/*********************************************************************
** Function: matrix_fun.....It's a structure
** Description: A structure defining pointers pointing to pointers. Create 2d arrays.
** Parameters: n: dummy variable representing each index in the string input.
** 			   **m1/**m2: The double pointer matrix vars.
** Pre-Conditions: Meow
** Post-Conditions: Meow meow
*********************************************************************/ 
struct matrix_fun {
	//Variable dummy for dictation, then thedouble arrrays. two of em.
	//two chain, two matrix. swag
	int n;
	int **m1;
	int **m2;
 
	void make_matrix();
};

//Will create 2d Dynamic Array and initialize it with random values
/*********************************************************************
** Function: make_matrix
** Description: populates a matrix and then creates a smaller matrix pops with sums.
** Parameters: m1/m2: These are the matrixs defined in the struct.
** Pre-Conditions: Inputs are valid numbers
** Post-Conditions: nothing
*********************************************************************/ 
void matrix_fun::make_matrix(){
	int q;
	cout << "Enter a value for the generation of randomness. If its negative we all die. " << endl;
	cin >> q;
	//this is stuff. lets make matrixes yayy!! randnum gen for init matrix.
   m1 = new int*[n];
   for(int i=0; i<n; i++)
      m1[i]=new int[n];

   for(int i=0; i<n; i++)
      for(int j=0; j<n; j++)
	 m1[i][j]= rand() %q;
	 
	 //Shnarf shnarf new matrix formed from the precursor of the last matrix superload.
	m2 = new int*[n-1];
   for(int i=0; i<n-1; i++)
      m2[i]=new int[n];

   for(int i=0; i<n-1; i++)
      for(int j=0; j<n-1; j++)
	 m2[i][j]= m1[i][j] + m1[i+1][j] + m1[i][j+1] + m1[i+1][j+1];;
}

//Will create 2d Dynamic Array and initialize it with random values
/*********************************************************************
** Function: main
** Description: Run everything here
** Parameters: game.n: dummy variable representing each index in the matrix input.
** 			   just make the matrix runnnn
** Pre-Conditions: all number inputs
** Post-Conditions: Sexy.
*********************************************************************/ 
int main(){
	// unleashed precursor to the glory of Sparta. game is set as an object of type matrix_SOMUCHFUN
   matrix_fun game;
   cout << " HOW BIG IS THY MATRIX PERIMATARRRRRRR RAWR RARW RWAR WOOOWWW" << endl;
   cin >> game.n;
   
   //RUN THE TRAP
   game.make_matrix();
   for(int i=0; i<game.n; i++) { 
      for(int j=0; j<game.n; j++) {
	  //Look at comment below 
	  cout << game.m1[i][j] << " ";
	  }
	cout << endl; 
	}
	cout << "And now, MAGIC!!!!!!! ~~~~~~!@~~~~~ :D btw using 3 works best" << endl << endl; 
	//Show me the money. Wait thats age of empires. Show me the matrix!
   for(int i=0; i<game.n-1; i++) {
      for(int j=0; j<game.n-1; j++) {
	 cout << game.m2[i][j] << " ";
	  }
	cout << endl;
	}
}