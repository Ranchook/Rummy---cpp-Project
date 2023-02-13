#ifndef __player_p
#define __player_p

#include "Player.h"
#include "card.h"
#include "stackItem.h"
#include <cstring>
#include <iostream>
using namespace std;

void Player::setName(char* Pname)
{
	char *newName = new char[strlen(Pname) + 1]; // allocating new Pname string
	strcpy(newName, Pname);
	Pname = newName;
	delete[] Pname; // deleting old string
}

void Player::setCard(Card* card) // adding a card to the hand
{
	Card **temp = new Card*[numInHand + 1];
	for (int i = 0; i < numInHand; i++)
		temp[i] = hand[i];
	numInHand++;
	temp[numInHand - 1] = card;
	delete[] hand;
	hand = temp;
}

Card * Player::getCard(int indx) const
{
	return hand[indx];
}

char* Player::getName() const
{
	return name;
}

char Player::isValidSign()
{
	char sign;
	cout << "Please enter card sign (H, S, C, D): ";
	cin >> sign;
	while (sign != 'H' && sign != 'S' && sign != 'C' && sign != 'D')
	{
		cout << "Please enter valid sign:  ";
		cin >> sign;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return sign;
}

int Player::isValidValue()
{
	int value;
	cout << "Please enter card value: ";
	while (!(cin >> value))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // cleaning 
		cout << "Enter a number not a char: ";
	}

	while (value < 1 || value > 13)
	{
		cout << "Please enter valid card value:  ";
		cin >> value;
	}
	return value;
}

int Player::getNumberOfCards() const
{
	return numInHand;
}

void Player::printHand() const
{
	int i;
	if (numInHand > 0)
	{
		cout << "Player cards: " << endl;
		for (i = 0; i < numInHand - 1; i++)
		{
			hand[i]->printCard();
			cout << ", ";
		}
		hand[i]->printCard();
		cout << endl;
	}
	else
		cout << "No Cards! " << endl;
}

Player::Player(char* Pname)
{
	if (Pname)
	{
		name = new char[(strlen(Pname) + 1)];
		strcpy(name, Pname);
	}
	numInHand = 0;
	hand = nullptr;
}

int Player::searchCardinHand(char sign, int val) const
{
	int i;
	for (i = 0; i < numInHand; i++)
	{
		if (hand[i]->getSign() == sign && hand[i]->getValue() == val)
			return i;
	}
	//if card not faiund return -1
	return -1;
}

Card * Player::extructCard(char char_c, int _val)// removing card from hand
{
	Card * c;
	Card **temp = new Card*[numInHand - 1];
	if (_val == 0)	// when player quits extracts 1st card in hand
	{
		char_c = hand[0]->getSign();
		_val = hand[0]->getValue();
	}
	int i, indx = searchCardinHand(char_c, _val); // keeping card indx
	while (indx < 0) // if search returned -1
	{
		cout << "No such card in hand! Please enter a new card:" << endl;
		char_c = isValidSign();
		_val = isValidValue();
		indx = searchCardinHand(char_c, _val);
	}

	c = hand[indx];
	if (indx < numInHand) // if not the last card
	{
		for (i = indx; i < numInHand - 1; i++) // "push back" array
			hand[i] = hand[i + 1]; // this part my not work
	}
	numInHand--;
	for (int i = 0; i < numInHand; i++)
		temp[i] = hand[i];
	delete[] hand;
	hand = temp;
	return c;
}

Player::~Player()
{
	delete[] name;
	delete[] hand;
}
#endif // !__player_p