#ifndef hw3_HPP
#define hw3_HPP
#include <iostream>
#include <cstdlib>


using namespace std;



struct card {
	
	string value;
	string suit;
};

class player {
	public:
	
	int cash;
	card mycard[5];
	string hand;	
	int TheScore;
	
	void player_init(){
		//cash = 50;
		for(int i = 0; i < 5; i++){
			mycard[i].value = " ";
			mycard[i].suit = " ";
		}
	}
	void potInit(){
		cash = 0;
	}

};


class deck{
	friend class StudPoker;
	friend class go_drawPoker;
	private:
	card myDeck[52];

	public:
		void initializor();
		void deckshuffle();
};


class card_games {
	protected:
	player totalpot;
	player players[6];
	deck mainDeck;
 	public:
	int Judgement(int amt);
	virtual void play()=0;	
	
};	
	
	




class StudPoker: public card_games {
	public:
		void play();
};


class go_drawPoker: public card_games {
	public:
		void play();
};




/* char choose_game() {
	char choose;
	
	cout << "What game would you like to play, press s for Stud poker" << endl;
	cout << "Or press d for Draw poker" << endl;
	cin >> choose;
	
	return choose;
} */




#endif



