#ifndef __player_h
#define __player_h

#pragma once
#include "card.h"

class Player
{
	int numInHand;
	char *name;
	Card** hand;
public:
	void setName(char* name);
	void setCard(Card* card);
	char* getName() const;
	Card *getCard(int indx) const;
	Card *extructCard(char char_c = '\0', int _val = 0);
	int searchCardinHand(char sign, int val) const;
	int getNumberOfCards() const;
	void printHand() const;
	Player(char* name);
	char isValidSign();
	int isValidValue();
	~Player();

};
#endif // !____player_h