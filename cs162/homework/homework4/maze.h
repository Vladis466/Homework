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
class floor {
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
	void move(int i){
		
		
		if(i < 5){
			locy = locy -1;
		}
		if(i > 4 && i < 15 ){
			locy = locy + 1;
		}
		if(i > 14 && i < 20){
			locy = locy - 1;
		}
	}
	
};

class Player: public Character {	
	friend class Game;
	protected:
		int keys;
		int invincibility;
	public:
		void move(){
			char direction = 'i'; //where are we we moving?
			//do{
				cout << "Enter w, a, s, or d to move, i to check invincibility, or k to check keys " << endl;
			while( direction == 'i' || direction == 'k'){
				cin >> direction;
				if( direction == 'k'){
					cout << "You have " << keys << " keys in your inventory.";
				}
				if(direction == 'i'){
					cout << "You have " << invincibility << " invincible moves left.";
				}
			}
				switch (direction){
				
					case 'w':
						locx = locx - 1;
						if(invincibility != 0){
							invincibility = invincibility - 1;
						}
					break;	
					
					case 'a':
						locy = locy - 1 ;
						if(invincibility != 0){
							invincibility = invincibility - 1;
						}						
					break;
					
					case 's':
						locx = locx + 1;
						if(invincibility != 0){
							invincibility = invincibility - 1;
						}						
					break;
						
					case 'd':
						locy = locy + 1;
						if(invincibility != 0){
							invincibility = invincibility - 1;
						}					
					break;
					
				}

			//}while(direction!=esc);
		}
	
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
		floor mazes[4];
	
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