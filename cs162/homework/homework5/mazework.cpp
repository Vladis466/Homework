/***********************
 ** program: maze.cpp
 ** Author: Vlad Predovic
 ** Date: 3/12/2015
 ** Description: Implements a game where we run around collecting keys
 ** opening doors, passing through levels and ultimately taking over the world.
 ** Input: Absolutely nothing
 ** Output: The game where we interact in REAL TIME
************************/

#include <iostream>
#include <stdio.h>	//for puts(" ")
#include<fstream>
#include "maze.h"



using namespace std;
 
	



//These functions below simply find the x and y positions of the ladders
//and entrances in order to have a location to reposition the player 
//when Johnny enters a level or gets his mind devoured by the pikmin.
/*********************************************************************
** Functions: FindEx, FindEy, FindBx, FinBy, FindCx, FindCy
** Description: Look above
** Parameters: int i, j: to search through the entire grid for the character
** Pre-Conditions: An input grid formatted into a double array of chars
** Post-Conditions: Returns the x or y position of the char in question as integer.
*********************************************************************/ 		
int floor::FindEx(){
	for (int i=0; i<20; i++){
		for (int j=0; j<30; j++){
			if(tiles[i][j] == 'E'){
			return i;
			}
		}
	}
}
int floor::FindEy(){
	//i will run through all the rows in the provided 2d char array
	for (int i=0; i<20; i++){
		//j will run through all the columns in the provided 2d char array
		for (int j=0; j<30; j++){
			//Searching for E
			if(tiles[i][j] == 'E'){
			// We return +1 because I want Johnny to start next to the entrance
			//not on top of the door you cannot stand on a closed gate theres no way out 
			//REMEMBER DUH LOGIC.
			return j + 1;
			}
		}
	}
}
int floor::FindAx(){
	for (int i=0; i<20; i++){
		for (int j=0; j<30; j++){
			//Same as above but return row position of ladder A
			if(tiles[i][j] == 'A'){
			return i;
			}
		}
	}
}
int floor::FindAy(){
	for (int i=0; i<20; i++){
		for (int j=0; j<30; j++){
			//Same as above but return column position of ladder A
			if(tiles[i][j] == 'A'){
			return j;
			}
		}
	}
}
int floor::FindBx(){
	for (int i=0; i<20; i++){
		for (int j=0; j<30; j++){
			//Same as above but return row position of ladder A
			if(tiles[i][j] == 'B'){
			return i;
			}
		}
	}
}
int floor::FindBy(){
	for (int i=0; i<20; i++){
		for (int j=0; j<30; j++){
			//Same as above but return column position of ladder A
			if(tiles[i][j] == 'B'){
			return j;
			}
		}
	}
}

	

	
//The functions below simply read the floors from the text files
//into the Matrix which is my program. Otherwise if there is no file it kicks you out.
//The code is replicated for floors A, B, and C.
/*********************************************************************
** Functions: readFloorA, readFloorB, readFloorC
** Description: Look above 
** Parameters: int n: Digit used to transfer the array of characters into our maze class
			   string fromfile: Used to input the text file. One line at a time saved into fromfile
** Pre-Conditions: A text file with the allotted names FloorA, FloorB, or FloorC
** Post-Conditions: None needed, We get out 2darray into the program
*********************************************************************/ 	
void Game::readFloorA(){
			int n = 0;
			string fromfile;
			ifstream myfile("FloorA.txt");
			if (myfile.is_open()){
				while(getline(myfile,fromfile,'\r')){
					mazes[0].tiles[n] = fromfile;
					n++;
				}
				myfile.close();
			} else {
			cout << "File is not open" << endl;
			}
			//mazes[0].printSc();
		}	
void Game::readFloorB(){
			int n = 0;
			string fromfile;
			ifstream myfile("FloorB.txt");
			if (myfile.is_open()){
				while(getline(myfile,fromfile,'\r')){
					mazes[1].tiles[n] = fromfile;
					n++;
				}
				myfile.close();
			} else {
			cout << "File is not open" << endl;
			}
			//mazes[1].printSc();
		}
void Game::readFloorC(){
			int n = 0;
			string fromfile;
			ifstream myfile("FloorC.txt");
			if (myfile.is_open()){
				while(getline(myfile,fromfile,'\r')){
					mazes[2].tiles[n] = fromfile;
					n++;
				}
				myfile.close();
			} else {
			cout << "File is not open" << endl;
			}
			//mazes[2].printSc();
		}
		
		
		
//The function below placy Johnny at the spot where he should be depending on his situation.
/*********************************************************************
** Functions: readFloorA, readFloorB, readFloorC
** Description: Using a series of gates the function will place Johnny at the location of A, B, or E after death or when entering a new level.
** Parameters: int i, j: Cycle through the entire 2d array searching for the character
			   int WhatMaze: This number depends on what level he is on.
			   int LevelsPassed: This number dictates whether or not Johnny has already beat a level
** Pre-Conditions: A text file with the allotted names FloorA, FloorB, or FloorC
** Post-Conditions: None needed, We get out 2darray into the program
*********************************************************************/ 			
void Game::PlaceJohnnyInit(int WhatMaze, int LevelsPassed){
			for (int i=0; i<20; i++){
				for (int j=0; j<30; j++){
					//we use this if statement to check what level the player is on
					//This allows us to then place the player in the correct starting location.
					if(WhatMaze == 0){
						if(LevelsPassed == 0){
						//If the player has not passed any levels then when will place him at the E starting spot
							if(mazes[0].tiles[i][j]=='E'){
								Johnny.locx = i; 
								Johnny.locy = j + 1;
								mazes[0].tiles[i][j+1] = 'P';	
							}
						} else {  //else we place him at the A spot. Simple, see!
							if(mazes[0].tiles[i][j]=='A'){
								Johnny.locx = i;
								Johnny.locy = j;
								mazes[0].tiles[i][j] = 'P';
							}
						}	
					}
					if(WhatMaze == 1){
//						if(LevelsPassed == 1){
							if(mazes[1].tiles[i][j]=='A'){ //Ran into issues here oh dear. Never Fixed it
								Johnny.locx = i;
								Johnny.locy = j;
								mazes[1].tiles[i][j] = 'P';
							}
//						}else{
//							if(mazes[1].tiles[i][j]=='B'){
//								Johnny.locx = i;
//								Johnny.locy = j + 1;
//								mazes[1].tiles[i][j] = 'P';
//							}
//						}
					}
					if(WhatMaze == 2){
						if(mazes[2].tiles[i][j]=='B'){ //This one is simple since theres only one starting spot we will always put Johnny here
							Johnny.locx = i;
							Johnny.locy = j;
							mazes[2].tiles[i][j] = 'P';
		     		}
				}					
			}
		}			
}

		
void Game::PlaceGhosts(int WhatMaze){  //Very similar to placing Johnny. Damn you Johnny
		for (int i=0; i<20; i++){
			for (int j=0; j<30; j++){
				if(mazes[WhatMaze].tiles[i][j]=='G'){ //If a G appears in our two d array
					pikmin.locx = i;  //The member that holds the location will be given 
					pikmin.locy = j;  //The coordinates of that G thus creating our pikmin
					mazes[WhatMaze].tiles[i][j] = 'G';	
				}
	    	}
		}
}

//The function play is the primary function in my program that creates the game and has all the different
//objects interacting. This function takes in an integer variable that decides what level you are in and
//what decisions to take from that point on.
/*********************************************************************
** Function: Play is my function.
** Description: This function will loop, placing the player in a position on the map and then calling all necessary 
** functions to create the appearance of the player traversing said map level. When he reaches a ladder, the program 
** responds accordingly through a series of integer variables acting as switches. 
** It is a messy method but effective.
** Parameters: int i: Keeps us in our loop while we are on the same level
			   int x: This counter is used to mark the movements of the ghost. When he dies it keeps him dead.
			   int b: Used as a return value because I was having issues returning the value of the input var.
			   int reset: Starts you over if the ghost kills you.
			   tempx,tempy,Gtempx,Gtempy: Used as temporary values for Johnny and the Ghost respectively
			   reset: 
** Pre-Conditions: Text files with the allotted names FloorA, FloorB, and FloorC.
** All the descriptive char values that create our maze.
**A main function that interacts with this function by feeding it our location.
** Post-Conditions: The return value is an integer.
*********************************************************************/ 	
int Game::Play(int level){
			
			int i = 0;  //gameEnderBender
			int x = 0;  //ghost movement
			int b = level; //to save and return the level were on
			int reset; //start over ghost slays you.
			Johnny.keys = 0; // We set Johnny's keys equal to 0 at each level to up the difficulty.
			Johnny.invincibility = 0; //Johnny's invincibility, self explanatory.
			int tempx, tempy, Gtempx, Gtempy;
			while(i!=1){  //While you haven't passed the level.

				reset = 0; //Counter 
				mazes[level].printSc();  //We call the print function for the required level
				mazes[level].printHmode(Johnny.locx, Johnny.locy);  //Calling print accessor function for 5 space radius
				
				
				tempx = Johnny.locx; //Set dummy values equal to Johnnys last location.
				tempy = Johnny.locy; 
				Gtempx = pikmin.locx; //Set dummy values equal to ghosts last location.
				Gtempy = pikmin.locy;
				
				
				mazes[level].tiles[Johnny.locx][Johnny.locy] = ' '; //Blank out Jhonnys last spot
				
				if(x != 31){  //This if clause makes our ghost disappear if we killed him.
				pikmin.move(x);				
				mazes[level].tiles[pikmin.locx][pikmin.locy] = 'G'; //we move the ghost before calculations.
				} else {
					pikmin.locy = 0;  //In order to make him disappear I place him on the border where the wall is
					pikmin.locx = 0;  
				}
				
				Johnny.move();  //Here Johnny's position changes but remember we have his old spot saved in case
				//he tries to do something dumb.
				
				if(mazes[level].tiles[Johnny.locx][Johnny.locy] == '#' || mazes[0].tiles[Johnny.locx][Johnny.locy] == 'E'){
					Johnny.locx = tempx;  //If we move to an illegal location, we put Johnny back using the dummy locators.
					Johnny.locy = tempy;
					cout << "Hah you ran in to a wall, loser" << endl;
				}
				
				
				if(mazes[level].tiles[Johnny.locx][Johnny.locy] == 'K'){ //Keys, pretty easy
					if(Johnny.keys < 3){  //DEM KEYS U HOLDING DOE
						Johnny.keys = Johnny.keys + 1;
					} else{
						cout << "You are holding too many keys" << endl;
						mazes[level].tiles[Johnny.locx][Johnny.locy] = 'K';//This way the key isn't taken
					}		
				}
				
				//invincibility counter if we grab a cherry ma'cherrie
				if(mazes[level].tiles[Johnny.locx][Johnny.locy] == 'C'){
					Johnny.invincibility = 20;    
				}
				//We found the exit, good job!!
				if(mazes[level].tiles[Johnny.locx][Johnny.locy] == 'X'){
					b = 7;			//
					i = 1;				
					cout << "Congratulations, you somehow survived my evil lair" << endl;	
					exit(1);
				}			
				
				//Interaction with ghost
				if(mazes[level].tiles[Johnny.locx][Johnny.locy] == 'G'){
					if(Johnny.invincibility == 0){											//YOU LOSE!
						cout << "YOU GOT EATEN HERMAGERD" << endl << endl << endl << endl;
						reset = 1;  //reset position.
						if(level == 1){
							cout << "you lost bye bye" << endl;
							exit(1);
						}
						if(level == 0){  ///We use the find functions to start our character over if he dies.
							Johnny.locx = mazes[0].FindEx();
							Johnny.locy = mazes[0].FindEy();  
						}else if(level == 1){
							Johnny.locx = mazes[1].FindAx();
							Johnny.locy = mazes[1].FindAy();
						} else {
							Johnny.locx = mazes[2].FindBx();
							Johnny.locy = mazes[2].FindBy();
						}
					} else {   //If his invincibility isn't 0, the ghosts movement counter is set to make him  'disappear'
						x = 30;
					}
				}
				
				//Doors
				if(mazes[level].tiles[Johnny.locx][Johnny.locy] == 'D'){
					if(Johnny.keys == 0){  //If you cant cross it we kick you back using our dummy values.
						Johnny.locx = tempx;
						Johnny.locy = tempy;
						cout << "Thou shalt not pass without thy keys" << endl;
					} else {
						Johnny.keys = Johnny.keys - 1;
					}
				}

				
				if(x != 31){
				x++; //ghost movement counter decides whether it goes left or right.
				}
				if(reset == 1){
					cout << "Would you like to quit? Press 1 to quit 0 to keep playing." << endl;
					cin >> i;					
				}
				if(x == 20){
					x = 0;    // Reset ghost movement counter So he keeps pathing.

				}
				
				
				if(mazes[level].tiles[Johnny.locx][Johnny.locy] == 'A'){
					char choice;
					cout << "Press u to go up or z to go down" << endl;	
					cin >> choice;
					if(choice == 'u' && level == 0){
						level = level + 1;
						cout << level << endl;
						b = level;
						i = 1;
					}
					if(choice == 'z'  && level != 0){
						level = level - 1;	
						cout << level << endl;
						b = level;
						i = 1;
					}
				}
				if(mazes[level].tiles[Johnny.locx][Johnny.locy] == 'B'){
					char choice;
					cout << "Press u to go up or z to go down" << endl;	
					cin >> choice;
					if(choice == 'u' && level == 1){
						level = level + 1;
						cout << level << endl;
						b = level;
						i = 1;
					}
					if(choice == 'z'  && level == 2){
						level = level - 1;	
						cout << level << endl;
						b = level;
						i = 1;
					}
				}
				

				mazes[level].locate(level);
				
				
				mazes[level].tiles[Gtempx][Gtempy] = ' ';	//Blank out previous ghost position
				mazes[level].tiles[Johnny.locx][Johnny.locy] = 'P';  //Depict the movements of player
				
				
					
				
			//system("CLS");
//				cout << i << endl;
//				cout << Johnny.invincibility << endl;
//				cout << x;
			}
			cout << endl << endl << endl << b << endl;
			
			return b;
			
		}
		


