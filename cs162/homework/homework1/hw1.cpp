/***********************
 ** program: hw1.cpp
 ** Author: Vlad Predovic
 ** Date: 1/19/2015
 ** Description: Implements the game of life! You choose the location and it gives you the option between
 ** a glider, a glider gun, or an oscillating BEAST.
 ** Input: Where you want to start and what type of creation you want
 ** Output: a matrix showing the patterns that occur
************************/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
// http://stackoverflow.com/questions/12777254/time-delay-in-c-usleep used for sleep function


using namespace std;

//This function copies a two dimensional array
/*********************************************************************
** Function: cloneWorld
** Description: Will clone the grid
** Parameters: Trueworld: The 2d array provided
** Pre-Conditions: two dimensional array of type int
** Post-Conditions: nada
*********************************************************************/ 
void cloneWorld(int TrueWorld[30][88], int NewWorld[30][88]) {
	
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 88; j++) {
		NewWorld[i][j] = TrueWorld[i][j];
		}
	}
}

//Pick what you want to run
/*********************************************************************
** Function: start_Choice
** Description: the provided matrix 
** Parameters: a: dummy variable representing each index in the string input.
** 			   str: the score the user used as an input
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/ 	
void start_Choice(int graph[][88]) {
	int row;
	int col;
	int choice;
	//Insert a cell that will set the area where you want the life to start around. 
	cout << " Our world consists of 22 rows and 80 colums. Insert a row number(1 through 22) where you want the game to start." << endl;
	cout << "Selecting a corner option might result in an end to the program. Pick values in the middle for best results" << endl << endl << endl;
	//The padding +3 is to account for ghost cells that wont be printed.
	cin >> row;
	row = row + 3;
	cout << "Now insert the column number of the coordinate you want.(1 through 80)" << endl;
	cin >> col;
	col = col + 3;
	cout << "Press 1: This will generate a fixed simple oscillator pattern." << endl;
	cout << "Press 2: Watch the glider move!!!." << endl;
	cout << "Press 3: Glider Gun Engage." << endl;
	cout << "Anything thing else will result in the assumption that choice 3 was preferred" << endl;
	cin >> choice;
	if(choice == 1) {
		graph[row][col] = 1, graph[row -2][col + 2] = 1, graph[row + 3][col + 2] = 1, graph[row][col + 5] = 1;
		graph[row + 1][col] =1, graph[row - 2][col + 3] =1, graph[row + 3][col + 3] = 1, graph[row + 1][col + 5] = 1;
		graph[row + 2][col] =1, graph[row - 2][col + 4] =1, graph[row + 3][col + 4] = 1, graph[row + 2][col + 5] = 1;
		
		graph[row + 6][col] = 1, graph[row + 5][col + 2] = 1, graph[row + 10][col + 2] = 1, graph[row + 6][col + 5] = 1;
		graph[row + 7][col] =1, graph[row + 5][col + 3] =1, graph[row + 10][col + 3] = 1, graph[row + 7][col + 5] = 1;
		graph[row + 8][col] =1, graph[row + 5][col + 4] =1, graph[row + 10][col + 4] = 1, graph[row + 8][col + 5] = 1;
			
		graph[row][col + 7] = 1, graph[row -2][col + 8] = 1, graph[row + 3][col + 8] = 1, graph[row][col + 12] = 1;
		graph[row + 1][col + 7] =1, graph[row - 2][col + 9] =1, graph[row + 3][col + 9] = 1, graph[row + 1][col + 12] = 1;
		graph[row + 2][col + 7] =1, graph[row - 2][col + 10] =1, graph[row + 3][col + 10] = 1, graph[row + 2][col + 12] = 1;
			
		graph[row + 6][col + 7] = 1, graph[row + 5][col + 8] = 1, graph[row + 10][col + 8] = 1, graph[row + 6][col + 12] = 1;
		graph[row + 7][col + 7] =1, graph[row + 5][col + 9] =1, graph[row + 10][col + 9] = 1, graph[row + 7][col + 12] = 1;
		graph[row + 8][col + 7] =1, graph[row + 5][col + 10] =1, graph[row + 10][col + 10] = 1, graph[row + 8][col + 12] = 1;
		
	} else if(choice == 2) {
		graph[row][col] = 1,  graph[row + 1][col] = 1;
		graph[row + 2][col] = 1,  graph[row][col + 1] = 1;
		graph[row + 1][col + 2] = 1;
	
	} else {
		graph[row][col] = 1, graph[row - 1][col + 34] = 1, graph[row][col + 10] = 1, graph[row - 1][col + 11] = 1;
		graph[row + 1][col] =1, graph[row - 1][col + 35] =1, graph[row + 1][col + 10] = 1, graph[row - 2][col + 12] = 1;
		graph[row][col + 1] =1, graph[row - 2][col + 34] =1, graph[row + 2][col + 10] = 1, graph[row -2][col + 13] = 1;
		graph[row + 1][col + 1] =1, graph[row - 2][col + 35] =1, graph[row + 3][col + 11] = 1, graph[row + 4][col + 12] = 1;
		
		graph[row + 4][col + 13] =1, graph[row - 1][col + 15] =1, graph[row][col + 16] = 1, graph[row + 1][col + 16] = 1;
		graph[row + 1][col + 14] =1, graph[row + 3][col + 15] =1, graph[row + 2][col + 16] = 1, graph[row+1][col + 17] = 1;
		
		graph[row -2][col + 20] =1, graph[row - 1][col + 20] =1, graph[row][col + 20] = 1, graph[row - 3][col + 22] = 1;
		graph[row - 2][col + 21] =1, graph[row - 1][col + 21] =1, graph[row][col + 21] = 1, graph[row + 1][col + 22] = 1;
		
		graph[row - 3][col + 24] =1, graph[row - 4][col + 24] =1, graph[row + 3][col + 11] = 1, graph[row][col + 10] = 1;
		graph[row + 1][col + 24] =1, graph[row + 2][col + 24] =1, graph[row + 3][col + 11] = 1, graph[row][col + 10] = 1;
	}

}

//The giver of life
/*********************************************************************
** Function: lifeorDeath
** Description: kills or gives life to cells depending on surrounding values
** Parameters: myWorld: The prior provided grid
** Pre-Conditions: Two dimensional array of type int
** Post-Conditions: no output
*********************************************************************/ 
//This function will run through the decisions of every cell
void lifeorDeath (int myWorld[30][88]) {
	
	
	int cloneGrid[30][88];
	
	cloneWorld(myWorld,cloneGrid);
	
	
	//This will cycle through a 22 by 80 range within the actual map leaving all the edges blank.
	for(int i=0; i<30; i++){
		for(int j=0; j<88; j++){
			//This var will count how many living cells surround current there are
			int dummy = 0;
			dummy = cloneGrid[i-1][j] +cloneGrid[i-1][j-1] +cloneGrid[i][j-1] +cloneGrid[i-1][j+1] +
					cloneGrid[i+1][j] +cloneGrid[i+1][j+1] +cloneGrid[i][j+1] +cloneGrid[i+1][j-1];
			
			if(dummy == 0 || dummy == 1 || dummy > 3) {
				myWorld[i][j] = 0;
			} 
			if(dummy == 3) {
				myWorld[i][j] = 1;	
			}
	//	cout << myWorld[i][j]; // ~~used to error check
		}
		cout << endl;
	}
	

}
		
		
		

//Will create 2d Dynamic Array and initialize it with random values
/*********************************************************************
** Function: print_Grid
** Description: prints the map
** Parameters: grid: The double array with the current life values
** Pre-Conditions: Insert the preconditioned double array
** Post-Conditions: void, none
*********************************************************************/ 
void print_Grid(int grid[30][88]) {
	//This will loop through each position in the graph 'world' and
	//output an X or space depending on the value of the location(1 or 0)
	for(int i=4; i<26; i++){
		for(int j=4; j<84; j++){
			if(grid[i][j] == 1){
				cout << "X";
			} else {
				cout << " " ;
			}
			//if(i == 0 || i == 30 || j == 0 || j == 22) {  attempt at a border was a failure
		//		cout << "#";
		//}
	}
	cout << endl; 
	}
}

//The main function yo
/*********************************************************************
** Function: main
** Description: Initiates and loops the program
** Parameters: world: The matrix that is our world
** 			   q: a switch that will propagate the loop
** Pre-Conditions:No preconditions, begins the program
** Post-Conditions: Will output the graphic display of the game of life.
*********************************************************************/ 
main() { 
	//dummy char to run each loop of the program
	string q = "y";
	int world[30][88];
	
	int counter = 0;
	
	
	//Creating the initial grid
	for(int i=0; i<30; i++){
		for(int j=0; j<88; j++){
		world[i][j]= 0;
		
		}	
	}
	
	cout << endl << endl << "Remember, to exit the program using the end of file hotkey(ctrl-z on Windows, ctrl-d on UNIX)" << endl;
	cout << "loading...."<< endl<< endl << endl << endl;
	sleep(3);
	// Will print out the starting cell pattern decided by the user
	start_Choice(world);
	print_Grid(world);
	cout << endl << endl << "First evolution begins now!" << endl;
	sleep(3);
	
	while(q=="y") {
		//save last iteration. Use this to check that the generations aren't frozen.(not working)
		//copy(world,past_World);
		//clear page. Currently not working
		//system("cls");
		usleep( 100000 );
		++counter;
		cout << "You are on evolution " << counter <<endl;
		
		lifeorDeath(world);
		print_Grid(world);
		
		if(counter == 75) {
			cout << "Move to the next generation? press y or n"<< endl;
			cout << endl << "Remember, to exit the program using the end of file hotkey(ctrl-z on Windows, ctrl-d on UNIX)" << endl;
			cin >> q;
			counter = 0;
		}
		
	} ;
	return 0;
}