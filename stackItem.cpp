#ifndef __stackitem_p
#define __tackitem_p
#include "stackItem.h"

stackItem::stackItem(Card * c, stackItem* n)
{
	card = c;
	next = n;
}

Card * stackItem::getCard() const
{
	return card;
}

stackItem * stackItem::getNextItem() const
{
	return next;
}
#endif // !__tackitem_h
