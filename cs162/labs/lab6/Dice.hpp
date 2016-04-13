#ifndef DICE_HPP
#define DICE_HPP

class Dice 
{
public:
	Dice();
	Dice(int numSides);
	virtual int roll() const;
protected:
	int numSides;
};

class LoadedDice1: public Dice{
	 LoadedDice1();
	 LoadedDice1(int numSides);
	 int roll() const;
};

class LoadedDice2: public Dice{
	LoadedDice2();
	LoadedDice2(int numSides);
	int roll() const;
};
#endif
