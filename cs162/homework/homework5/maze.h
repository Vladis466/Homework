/***********************
 ** program: maze.h
 ** Author: Vlad Predovic
 ** Date: 3/12/2015
 ** Description: Header file for a game where we run around collecting keys
 ** opening doors, passing through levels and ultimately taking over the world.
 ** This would be the main file where the operations alternating between levels are ran.
 ** Input: Absolutely nothing
 ** Output: A frame of the game the user interacts with in real time
************************/

#ifndef maze_h
#define maze_h
#include <iostream>
#include <cstdlib>


using namespace std;
#include <iostream>
#include <stdio.h>	//for puts(" ")
#include <cstdlib>	//for clear screen
#include <time.h>	//for initializing srand() function
#include<fstream>
#include <math.h>


using namespace std;
 
 
 //This class is used to represent each floor in the maze. The functions
// in this class are used to print the level or locate certain aspects of the level.
/*********************************************************************
** Functions: printSc, Find?(x||y), locate
** Description: printSc prints the map. Find locates ladders and the starting point to use as a reference
** and locate places the characters in their respective locations for the levels provided.
** PrintHmode will print the print the map so that the player can only see a distance of 5 spaces from his location.
** Parameters: int i, j: to search through the entire grid for the characters
			   string tiles: the rows of our map. 20 rows by 30 columns.
			   Posx, Posy: The coordinates of Johnny used to develop the hard mode.
** Pre-Conditions: An input grid formatted into a double array of chars
** Post-Conditions: Returns the x or y position of the char in question as integer.
*********************************************************************/ 		
class Floor {
	friend class Game;
	
	protected:
		string tiles[20];   //our complete matrix represented by an array of strings.
		
	
	public:
		void printSc() {  //Casually prints out the entire map
			for (int i=0; i<20; i++){
				for (int j=0; j<30; j++){
					cout << tiles[i][j];
				}
				cout << endl;
			}
		}
		
		
		void printHmode(int Posx, int Posy){     //casually prints out a sight block of 5 spaces from the player.
			int dummy;
				for (int i=(Posx-5); i<(Posx+5); i++){
					for (int j=(Posy-5); j<(Posy+5); j++){
						dummy = 1;
						if(i < 0){ dummy = 0;}			//We have these checks in place so that
						if(j < 0){ dummy = 0;}			//we avoid leaving the acceptable range
						if(i > 19){ dummy = 0;}			// of our two dimensional array that is
						if(j > 29){ dummy = 0;}			//the maze which would result in a seg fault.
						
						if(dummy == 1){
							cout << tiles[i][j];		//If we are in our maze, print.
						}
					}
					cout << endl;
				}
		}
		
		int FindEx();
		int FindEy();
		int FindAx();
		int FindAy();
		int FindBx();
		int FindBy();
		
		void locate(int whatLevel){
			switch(whatLevel){
				case 0:
					tiles[4][14] = 'A';
				break;
				case 1:
					tiles[4][14] = 'A';
					tiles[11][14] = 'B';
				break;
				case2:
					tiles[11][14] = 'B';
				break;
			}
		}


};







class Character {   //abstract class
	friend class Game;
	
 	protected:
	
		int locx;
		int locy;
		char symbol;
		
	/* public:
		virtual void move(); */
	 
};
	
class Ghost: public Character {	
	
	public:
	void move(int Jlocx,int Jlocy, int stop){
		int x;
		int dist;
		// if the input stop = 31 then we do not move because we are toasted.
		
		dist = abs((Jlocx-locx)) + abs((Jlocy-locy)); //distance from player to ghost
	
		if(dist > 5 && stop != 31){	
			x = rand() % 4;	//Random movement of our ghost.

			if(x == 0 && locy != 0){  //make sure our ghost doesn't fall of the world using conditions
				locy = locy -1;  //and if so then move!!!
			}
			if(x == 1 && locy < 18){
				locy = locy + 1;
			}
			if(x == 2 && locx != 0){
				locx = locx -1;
			}
			if(x == 3 && locx != 18){
				locx = locx + 1;
			}
		}
//IF YOU GET TO CLOSE HE WILL RUN YOU DOWN. RUN YOU DOWN I SAY.
		if(dist < 5 && stop != 31){ 
			if( abs((Jlocx-locx)) > abs((Jlocy-locy))){ //Farther in x or y direction?
				if(Jlocx > locx){  //is he on the left or right?
					locx = locx + 1; //run that way!
				} else { //...repeat logic for all directions.
					locx = locx - 1;
				}
			} else {
				if(Jlocy > locy){
					locy = locy + 1;
				} else {
					locy = locy - 1;
				}				
			}
		}
	}
	
};

class Player: public Character {	
	friend class Game;
	protected:
		int keys;   //Keys held by our character. Accessed by pressing k in-game.
		int invincibility;
	public:
		void move();
	
		void addRemKeys(){
		
			if(keys==3){
				cout << "You cannot hold any more keys" << endl;
			}	
		}
	
};	
	
//This class is meant to interacgt with all other classes and holds the key functions of the game
//Since this is a header file and all of these functions are explained 
//in the implementation file we omit an explanation of the functions.
/*********************************************************************
** Members: Johnny, pikmin, mazes[]
** Description: This class brings together our player, ghosts, and maze. Makes them interact.
*********************************************************************/ 		
class Game {
	
	public:
		Player Johnny;
		Ghost pikmin;
		Floor mazes[4];
	
	public:
		void readFloorA();
		void readFloorB();
		void readFloorC();
		
		void placePeople(int level, int levsPassed){
			
			PlaceJohnnyInit(level, levsPassed);
			
			PlaceGhosts(level);
			//mazes[level].printSc();
		}
		
		void PlaceJohnnyInit(int WhatMaze, int LevelsPassed);
		
		void PlaceGhosts(int WhatMaze);
		
		int Play(int level);
		
		
		
			
	
		
};







#endif