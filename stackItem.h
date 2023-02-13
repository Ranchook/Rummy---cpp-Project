#ifndef __stackitem_h
#define __stackitem_h

#pragma once
#include "card.h"

class stackItem
{
	Card* card;
	stackItem* next;

public:
	stackItem(Card* c, stackItem* n = nullptr);
	Card* getCard()const;
	stackItem* getNextItem()const;
};
#endif // !__tackitem_h