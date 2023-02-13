#ifndef __set_p
#define __set_p
#include "Set.h"

using namespace std;

Set::Set() // constructor
{
	howManyCards = 0;
	cards = nullptr;
}

Set::Set(const Set &s)        // copy constructor
{
	howManyCards = s.howManyCards;
	cards = new Card*[howManyCards];
	for (int i = 0; i < howManyCards; i++)
		cards[i] = s.cards[i];
}

void Set::addCard(Card *c)                    // adding a card to set
{
	Card **temp = new Card*[howManyCards + 1]; 
	for (int i = 0; i < howManyCards; i++)
		temp[i] = cards[i];		// copying old set to new one
	howManyCards++;				// increasing set size
	temp[howManyCards - 1] = c;	// adding new card to set
	delete[] cards;
	cards = temp;	 //assigning as the 'formal' set
}

Card* Set::extructCard(char char_c, int int_val)  //extruct card from set
{
	int indx, i;
	Card * c;
	indx = searchInSet(char_c, int_val); // saving card indx
	c = cards[indx]; // saving the card
	Card **temp = new Card*[howManyCards-1];  //new array for allocating memory
	
	if (indx == 0)
	{
		for (i = 1; i < howManyCards; i++) // "push back" array
			temp[i-1] = cards[i];
		delete[] cards;
		cards = temp;
		howManyCards--;
		return c;
	}

	if (indx < howManyCards) // if not the last card
	{
		for (i = indx; i < howManyCards - 1; i++) // "push back" array
			cards[i] = cards[i + 1];
	}
	howManyCards--;
	for (i = 0; i < howManyCards; i++)
			temp[i] = cards[i];
	
	delete[] cards;
	cards = temp;
	return c;  //returning the card
}

bool Set::isValidset()const  // check if the set is ok
{
	if (howManyCards >= 3 && (isSameValueSerial() || isSequential())) // check if  less then 3 numbers and if the set is goood
		return true; // if does, returning true
	return false;
}

bool Set::isEmpty()const    //checking if there is cards in set
{
	if (howManyCards > 0) return false;
	return true;
}

bool Set::isSameValueSerial()const // different sign same number
{
	for (int i = 0; i < howManyCards - 1; i++) // compare card i
	{
		for (int k = i + 1; k < howManyCards; k++) // with rest of cards
		{
			if (cards[i]->getSign() == cards[k]->getSign()) // checking cards sign
				return false;
			if (cards[i]->getValue() != cards[k]->getValue())  // checking cards value
				return false;
		}
	}
	return true; // if the cards match, sending true
}

bool Set::isSequential() const	// same sign different number
{
	for (int i = 0; i < howManyCards - 1; i++)
	{
		if (cards[i]->getSign() == cards[i + 1]->getSign())  //if different sign, return false
		{

			if (cards[i]->getValue() + 1 != cards[i + 1]->getValue())   //is rising series? if so, falsh				
				return false;
		}
		else return false;
	}
	return true; // if the series are ok then return true
}

void Set::printSet() //printing the sets
{
	int i = 0;
	if (!isEmpty()) //first checking if there is emptysets.
	{
		for (i; i < howManyCards - 1; i++)
		{
			cards[i]->printCard(); // printing cards
			cout << ", ";
		}
		cards[i]->printCard(); // printing last card
		cout << endl;
	}
	else
		cout << "Empty set! " << endl << endl; // if set is empty
}

int Set::searchInSet(char sign, int value)          //searching card in set
{
	int i;
	for (i = 0; i < howManyCards; i++)
	{
		if (cards[i]->getSign() == sign && cards[i]->getValue() == value) // if cards match, index return
			return i;
	}
	cout << "No such card in set!" << endl;
	return -1;

}

void Set::swap(Card &min, Card &c)
{
	Card temp = min;
	min = c;
	c = temp;
}

void Set::sortSet()  // sorting in ascending order the set.
{	
	Card *minValue;
	int i, j, flag = 0;
	for (i = 0; i < howManyCards-1; i++)
	{
		minValue = cards[i];
		for (j = i + 1; j < howManyCards; j++)
		{
			if (cards[j]->getValue() < minValue->getValue())
			{
				minValue = cards[j];
				flag++;
			}
		}
		//putting the card with the smallet value first
		if (flag != 0)
			swap(*minValue, *cards[i]);
			
	}
}

Set:: ~Set()  // destructor
{
	delete[] cards;
}
#endif // !__set_p