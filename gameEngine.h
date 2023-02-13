#ifndef __gameengine_h
#define __gameengine_h

#pragma once

#include "CashierStack.h"
#include "Player.h"
#include "Set.h"

class gameEngine
{
	int howManySets;
	int howManyPlayers;
	Card cards[104];
	CashierStack deck;
	CashierStack trash;
	Set ** boardSets;
	Player** players;
	int playerTurn = 0; // varaible to help with the player turn, to know which turn is know.

public:
	gameEngine();
	void cardCreate();
	void dealCards();
	void startgame();
	Card **playedCards; //baackup array to use for rollback, if needed.
	Card *rollbackTrash;
	bool turn(Player &p);
	bool endTurn(Player * p);  //before sending to turn, we check here if the sets are correct

	void drawOptions() const; // showing the first 3 optioons to the player. 
	bool drawing(Player &p); //choosing option
	void removePlayer(Player* p);

	void printOptions() const; // showing the rest of the options 
	bool options(Player &p); // the switch case of the options 

	Card* handToSet(Player *p, int setIndx = 0); // we deliver the cards to the set
	int chooseSet(int howManySets); // chosing which set we want
	void moveCards(Player* p); //between sets, look on declration

	void printBoard(Set **Sets) const;
	int validInt(); // we check if the input of int is ok
	void rollback(Set ** oldSets, int oldSetsNum, int oldHandNum, Player *p); // if need to roolback, its done here
	~gameEngine(); //destruction
};
#endif // !___gameengine_h
