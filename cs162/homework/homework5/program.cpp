/***********************
 ** program: program.cpp
 ** Author: Vlad Predovic
 ** Date: 3/12/2015
 ** Description: Implements a game where we run around collecting keys
 ** opening doors, passing through levels and ultimately taking over the world.
 ** This would be the main file where the operations alternating between levels are ran.
 ** Input: Absolutely nothing
 ** Output: The game where we interact in REAL TIME
************************/
#include <iostream>
#include <cstdlib>
#include "maze.h"

using namespace std;


//My main function runs a loop comprised of all the existing levels in the system
//This greatly simplifies the complexity of the code which I believe to be the 
//ultimate goal.
/*********************************************************************
** Functions: FindEx, FindEy, FindBx, FinBy, FindCx, FindCy
** Description: Look above
** Parameters: int whereAmI: What level are we on? To be used by functions of class game
			   int LevelsPassed: To be used to place our character we keep in mind how many levels are passed.
** Pre-Conditions: none.
** Post-Conditions: none.
*********************************************************************/ 	
int main(){
	int whereAmI = 0;
	// The integer count levelsPassed begins at 0 because it increments at the beginning of the loop
	//You cannot have beaten -1 levels, absolute impossibility
	int LevelsPassed = -1;
	Game play;
	
	while(whereAmI < 3){
		LevelsPassed++;
		if(whereAmI == 0){
		play.readFloorA();
		play.placePeople(whereAmI, LevelsPassed);
		whereAmI = play.Play(whereAmI);
		}
		
		if(whereAmI == 1){
		play.readFloorB();
		play.placePeople(whereAmI, LevelsPassed);
		whereAmI = play.Play(whereAmI);
		}

		if(whereAmI == 2){
		play.readFloorC();
		play.placePeople(whereAmI, LevelsPassed);
		whereAmI = play.Play(whereAmI);
		}

	}
	
	//Oh joy, you won.
	if(whereAmI == 7){
		cout << "Congratulations, you somehow survived my evil lair" << endl;		
	}
	return 0;	
	
}

