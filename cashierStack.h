#ifndef __cashierstack_h
#define __cashierstack_h

#pragma once
#include "stackItem.h"
#include <iostream>
class CashierStack {

private:
	stackItem* head;
	int numInDeck;

public:

	CashierStack();
	~CashierStack();

	Card* pop();

	void push(Card* c);

	void shuffle();

	void shuffleNitem(int n);

	//void printStackForDeBugOnly()const;

	int getNumInDeck() const;
};
#endif // !__cashierstack_h