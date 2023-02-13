#ifndef __set_h
#define __tset_h
#include <iostream>
#pragma once
#include "card.h"

class Set
{
	int howManyCards;
	Card** cards;

public:
	Set(); // constructor
	Set(const Set &s); // copy constructor
	void addCard(Card *c); // adding a card to set
	Card* extructCard(char char_c, int int_val); //removing a card from set
	void swap(Card &min, Card &c);
	void sortSet();
	bool isValidset() const;
	bool isEmpty() const;
	bool isSameValueSerial() const;
	bool isSequential() const;
	void printSet();	// can't use const due to isEmpty()
	int searchInSet(char sign, int value); // searching a card in the set, returning his index
	~Set();
};
#endif // !__set_h