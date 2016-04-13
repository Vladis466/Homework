#include <iostream>
#include <stdlib.h>

using namespace std;


struct matrix_fun {
	int n;
	int **m1;
	int **m2;
 
	void make_matrix();
};

void matrix_fun::make_matrix(){
   m1 = new int*[n];
   for(int i=0; i<n; i++)
      m1[i]=new int[n];

   for(int i=0; i<n; i++)
      for(int j=0; j<n; j++)
	 m1[i][j]= rand() %5;
	 
	m2 = new int*[n-1];
   for(int i=0; i<n-1; i++)
      m2[i]=new int[n];

   for(int i=0; i<n-1; i++)
      for(int j=0; j<n-1; j++)
	 m2[i][j]= m1[i][j] + m1[i+1][j] + m1[i][j+1] + m1[i+1][j+1];;
}

int main(){
   matrix_fun game;
 
   cin >> game.n;

   game.make_matrix();
   for(int i=0; i<game.n; i++) { 
      for(int j=0; j<game.n; j++) {
	  cout << game.m1[i][j];
	  }
	cout << endl; 
	}
	cout << "And now, MAGIC!!!!!!! ~~~~~~!@~~~~~ :D btw using 3 works best" << endl << endl; 
   for(int i=0; i<game.n-1; i++) {
      for(int j=0; j<game.n-1; j++) {
	 cout << game.m2[i][j];
	  }
	cout << endl;
	}
}