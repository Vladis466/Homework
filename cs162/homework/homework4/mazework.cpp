#include <iostream>
#include <stdio.h>	//for puts(" ")
#include <cstdlib>	//for clear screen
#include <time.h>	//for initializing srand() function
#include<fstream>




using namespace std;
 
class floor {
	friend class Game;
	
	protected:
		string tiles[20];
		
	
	public:
		void printSc() {
		
			for (int i=0; i<20; i++){
				for (int j=0; j<30; j++){
					cout << tiles[i][j];
				}
				cout << endl;
			}
		
		}	
		
		int FindEx(){
			for (int i=0; i<20; i++){
				for (int j=0; j<30; j++){
					if(tiles[i][j] == 'E'){
					return i;
					}
				}
			}
		}
		int FindEy(){
			for (int i=0; i<20; i++){
				for (int j=0; j<30; j++){
					if(tiles[i][j] == 'E'){
					return j + 1;
					}
				}
			}
		}
		int FindAx(){
			for (int i=0; i<20; i++){
				for (int j=0; j<30; j++){
					if(tiles[i][j] == 'A'){
					return i;
					}
				}
			}
		}
		int FindAy(){
			for (int i=0; i<20; i++){
				for (int j=0; j<30; j++){
					if(tiles[i][j] == 'A'){
					return j;
					}
				}
			}
		}
		int FindBx(){
			for (int i=0; i<20; i++){
				for (int j=0; j<30; j++){
					if(tiles[i][j] == 'B'){
					return i;
					}
				}
			}
		}
		int FindBy(){
			for (int i=0; i<20; i++){
				for (int j=0; j<30; j++){
					if(tiles[i][j] == 'B'){
					return j;
					}
				}
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
	
	
class Game {
	
	public:
		Player Johnny;
		Ghost pikmin;
		floor mazes[4];
	
	public:
		void readFloorA(){
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
		void readFloorB(){
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
		void readFloorC(){
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
		
		void placePeople(int level, int levsPassed){
			
			PlaceJohnnyInit(level, levsPassed);
			
			PlaceGhosts(level);
			

			//mazes[level].printSc();
		}
		
		void PlaceJohnnyInit(int WhatMaze, int LevelsPassed){
			for (int i=0; i<20; i++){
				for (int j=0; j<30; j++){
					if(WhatMaze == 0){
						if(LevelsPassed == 0){
							if(mazes[0].tiles[i][j]=='E'){
								Johnny.locx = i;
								Johnny.locy = j + 1;
								mazes[0].tiles[i][j+1] = 'P';	
							}
						} else {
							if(mazes[0].tiles[i][j]=='A'){
								Johnny.locx = i;
								Johnny.locy = j + 1;
								mazes[0].tiles[i][j+1] = 'P';
							}
						}	
					}
					if(WhatMaze == 1){
//						if(LevelsPassed == 1){
							if(mazes[1].tiles[i][j]=='A'){
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
						if(mazes[2].tiles[i][j]=='B'){
							Johnny.locx = i;
							Johnny.locy = j;
							mazes[2].tiles[i][j] = 'P';
							
							
						}
					}					
				}
			}			
		}
		
		void PlaceGhosts(int WhatMaze){
			for (int i=0; i<20; i++){
				for (int j=0; j<30; j++){
					if(mazes[WhatMaze].tiles[i][j]=='G'){
						pikmin.locx = i;
						pikmin.locy = j;
						mazes[WhatMaze].tiles[i][j] = 'G';
						
					}
				}
			}
		}
		
		int Play(int level){
			
			int i = 0;  //gameEnderBender
			int x = 0;  //ghost movement
			int b = level; //to save and return the level were on
			int reset= 0; //start over ghost gotcha
			Johnny.keys = 0;
			Johnny.invincibility = 0;
			int tempx, tempy, Gtempx, Gtempy;
			while(i!=1){  //While a ghost hasn't devoured your soul.
				
				reset = 0;
				mazes[level].printSc();
				tempx = Johnny.locx;
				tempy = Johnny.locy;
				Gtempx = pikmin.locx;
				Gtempy = pikmin.locy;
				mazes[level].tiles[Johnny.locx][Johnny.locy] = ' ';
				if(x != 31){
				pikmin.move(x);				
				mazes[level].tiles[pikmin.locx][pikmin.locy] = 'G'; //we move the ghost before calculations.
				} else {
					pikmin.locy = 0;
					pikmin.locx = 0;
				}
				
				Johnny.move();
				
					if(mazes[level].tiles[Johnny.locx][Johnny.locy] == '#' || mazes[0].tiles[Johnny.locx][Johnny.locy] == 'E'){
						Johnny.locx = tempx;
						Johnny.locy = tempy;
						cout << "Hah you ran in to a wall, loser" << endl;
					}
					if(mazes[level].tiles[Johnny.locx][Johnny.locy] == 'K'){
						if(Johnny.keys < 3){  //DEM KEYS U HOLDING DOE
							Johnny.keys = Johnny.keys + 1;
						} else{
							cout << "You are holding too many keys" << endl;
							mazes[level].tiles[Johnny.locx][Johnny.locy] = 'K';
						}		
					}
					if(mazes[level].tiles[Johnny.locx][Johnny.locy] == 'C'){
						Johnny.invincibility = 20;
					}
					if(mazes[level].tiles[Johnny.locx][Johnny.locy] == 'X'){
						b = 7;
						i = 1;
						cout << "Congratulations, you somehow survived my evil lair" << endl;	
						exit(1);
					}
					if(mazes[level].tiles[Johnny.locx][Johnny.locy] == 'G'){
						if(Johnny.invincibility == 0){											//YOU LOSE!
							cout << "YOU GOT EATEN HERMAGERD" << endl << endl << endl << endl;
							reset = 1;  //reset position.
							if(level == 0){
								Johnny.locx = mazes[0].FindEx();
								Johnny.locy = mazes[0].FindEy();
							}else if(level == 1){
								Johnny.locx = mazes[1].FindAx();
								Johnny.locy = mazes[1].FindAy();
							} else {
								Johnny.locx = mazes[2].FindBx();
								Johnny.locy = mazes[2].FindBy();
							}
						} else {
							x = 30;
						}
					}
					if(mazes[level].tiles[Johnny.locx][Johnny.locy] == 'D'){
						if(Johnny.keys == 0){
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
						x = 0;    // Reset ghost movement counter.

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
					
					mazes[0].tiles[4][14] = 'A';
					mazes[1].tiles[4][14] = 'A';
					mazes[1].tiles[11][14] = 'B';
					mazes[2].tiles[11][14] = 'B';
					//mazes[2].tiles[Johnny.locx][Johnny.locy] = 'B';
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
		
		
			
	
		
};








int main(){
	int whereAmI = 0;
	int LevelsPassed = -1;
	Game play;
	
	while(whereAmI < 3){
		LevelsPassed++;
		if(whereAmI == 0){
		play.readFloorA();
		play.placePeople(whereAmI, LevelsPassed);
		whereAmI = play.Play(whereAmI);
		cout << endl << endl << endl << whereAmI << endl << endl;
		}
		
		if(whereAmI == 1){
		play.readFloorB();
		play.placePeople(whereAmI, LevelsPassed);
		whereAmI = play.Play(whereAmI);
		}

		if(whereAmI == 2){
		play.readFloorC();
		play.placePeople(whereAmI, LevelsPassed);
		play.Play(whereAmI);
		}

	}
	
	if(whereAmI == 7){
		cout << "Congratulations, you somehow survived my evil lair" << endl;		
	}
	return 0;	
	
}

