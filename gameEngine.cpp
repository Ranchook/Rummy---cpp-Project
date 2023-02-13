#ifndef __gameengine_p
#define __gameengine_p
#include "gameEngine.h"
using namespace std;

gameEngine::gameEngine() //constructor
{
	howManyPlayers = 0;            //init players
	players = new Player*[howManyPlayers];
	howManySets = 0;              //init sets
	boardSets = new Set *[howManySets];
	cardCreate();                 //init cards
	for (int i = 0; i < 104; i++) // create deck
		deck.push(&cards[i]);
	deck.shuffle();
}

void gameEngine::cardCreate()   //creating the cards and dividing them
{
	int i, j, k = 0;
	for (j = 0; j < 2; j++)	//there are 8 sets of cards.
	{
		for (i = 0; i < 13; i++)  
		{
			cards[i + k].setCard('H', i + 1);
			cards[i + 13 + k].setCard('C', i + 1);
			cards[i + 26 + k].setCard('D', i + 1);
			cards[i + 39 + k].setCard('S', i + 1);
		}
		k = 52;
	}
}

void gameEngine::startgame() // the game start here
{
	int i = 0;
	char Pname[50];
	cout << "How many players are playing? 2-7 players: ";  // the game is for 2-7 players
	howManyPlayers = validInt(); // checking for valid int value (and not char)
	while (howManyPlayers > 7 || howManyPlayers < 2)  //checking for 2-7 players
	{
		cout << "Please enter valid amount of players 2-7: ";
		howManyPlayers = validInt();
	}

	players = new Player*[howManyPlayers];	//allocating the players names
	for (i = 0; i < howManyPlayers; i++)
	{
		int flag = 0;
		cout << "Enter player " << i + 1 << " name: ";
		cin >> Pname;
		for (int k = 0; k < i; k++)
		{
			if (flag > 0)
			{
				k = 0;
				flag = 0;
			}
			if (!strcmp(Pname, players[k]->getName()))
			{
				cout << "There is already someone with that name, please choose a different name:" << endl;
				cin >> Pname;
				flag++;
				k = -1;
			}
		}
		players[i] = new Player(Pname);
	}

	dealCards();
	trash.push(deck.pop());	//first card to trash pile
	cout << "*Please use caps lock when choosing cards" << endl;
	while (turn(*players[playerTurn])) // starting the game!
	{
		if (playerTurn == howManyPlayers)
			playerTurn = 0;	// first player turn again
		printBoard(boardSets);
	}
	cout << "The winner is: " << players[playerTurn]->getName() << endl;
}

void gameEngine::dealCards() // here each players get 14 cards.
{
	for (int k = 0; k < howManyPlayers; k++)
		for (int i = 0; i < 14; i++)
			players[k]->setCard(deck.pop()); // pushing the cards to the player hand.
}

int gameEngine::validInt() // checking if the input int is ok.
{
	int i;
	while (!(cin >> i))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // cleaning buffer.
		cout << "Enter a number not a char: ";
	}
	return i; // if int is ok, returning the int.
}

void gameEngine::drawOptions()const
{
	cout << "What would you like to do?" << endl;
	cout << "1. Draw from deck." << endl;
	cout << "2. Draw from trash." << endl;
	cout << "3. Quit like a loser... :(" << endl;
}

bool gameEngine::drawing(Player & p) 
{
	int choose;
	while (1)
	{
		drawOptions();
		cout << endl << "your choice is: ";
		choose = validInt();
		switch (choose)
		{
		case 1: //draw card from deck
		{
			rollbackTrash = NULL;
			if (deck.getNumInDeck() == 0) //if deck is empty
			{
				cout << "No more cards in deck, select another option!" << endl << endl;
				break;
			}
			p.setCard(deck.pop()); //draw card from deck
			return true;
		}
		case 2: // draw card from trash pile
		{
			rollbackTrash = trash.pop();
			p.setCard(rollbackTrash);
			return true;
		}
		case 3: //player quits the game
		{
			removePlayer(&p);
			return false;    //quitting
		}
		default:
			cout << "Please enter a valid option!" << endl;
		}
	}
}

void gameEngine::removePlayer(Player * p) // removing the player
{
	int i = 0, playerIndx = 0, cardsInHand = p->getNumberOfCards();//keeping the players amount of cards.

	while (p->getName() != players[playerIndx]->getName())
		playerIndx++;

	for (i = 0; i < cardsInHand; i++)
		deck.push(p->extructCard());     //returning cards to deck
	deck.shuffle();
	howManyPlayers--;
	
	if (playerIndx != howManyPlayers) // if not the last player
	{
		//create a new player pointer to save last player's data
		Player *last = new Player(players[howManyPlayers]->getName());
		int lastCardNum = players[howManyPlayers]->getNumberOfCards();

		//transfer all his cards
		for (i = 0; i < lastCardNum; i++)
			last->setCard(players[howManyPlayers]->getCard(i));

		for (i = playerIndx; i < howManyPlayers; i++)
			players[i] = players[i + 1];	//pushback array
		cout << p->getName() << " just quit! what a loser..." << endl;
		delete players[howManyPlayers];	//delete last player
		players[howManyPlayers - 1] = last;	//put him back in his place
		return;
	}
	cout << p->getName() << " just quit! what a loser..." << endl;
	delete players[howManyPlayers];
}

void gameEngine::printOptions()const 
{
	cout << "What would you like to do?" << endl;
	cout << "1. Create new set." << endl;
	cout << "2. Add to existing set a card from hand." << endl;
	cout << "3. Allocate between existing sets." << endl;
	cout << "0. End turn." << endl;
}

bool gameEngine::options(Player & p) 
{
	int i = 0, choose, StartCardsInHand;
	StartCardsInHand = p.getNumberOfCards(); // keeping the amount of cards in the player hand
	playedCards = new Card*[1]; //allocating first memory of cards that we might use in the rollback later on.
	while (1)
	{
		if (StartCardsInHand == 0) // checking if the player cards in hand
			return true;
		p.printHand();
		printOptions();
		cout << endl << "Your choice is: ";
		choose = validInt(); // checking if the iput is valid
		switch (choose)
		{
		case 1: // create new set
		{
			Set **tempSets = boardSets; // keeping the old sets
			boardSets = new Set*[howManySets + 1];
			for (int k = 0; k < howManySets; k++)
				boardSets[k] = tempSets[k];		//copy the sets
			boardSets[howManySets] = new Set; // new set
			howManySets++;
			delete[] tempSets;
			break;
		}
		case 2: // Put cards in existing set
		{
			if (howManySets == 0) // if no set, back to options
				cout << "Please create a set before putting cards" << endl;
			else // if the player adding card to some set
			{
				Card ** Cardtemp = playedCards; // temp for cards that in the player hand
				playedCards = new Card*[i + 1]; // here we put cards for later use if needed roolback
				for (int k = 0; k < i; k++)
					playedCards[k] = Cardtemp[k];
				if (howManySets == 1)
					playedCards[i] = handToSet(&p); //putting the card in the set. using defalue value 0 -> set 1
				else
					playedCards[i] = handToSet(&p, chooseSet(howManySets));//putting the card in the set
				i++;
				delete[] Cardtemp;
			}
			break;
		}
		case 3: // the third options is to switch cards between sets
		{
			if (howManySets < 2) // if one set or less then back to options
			{
				cout << "Not enough sets, please select a different option" << endl;
				break;
			}
			else
			{
				printBoard(boardSets); // printing and showing the sets to player
				moveCards(&p); // the actual moving happen in this funcion
				break;
			}
		}
		case 0: // the last option is to end turn
		{
			return endTurn(&p); // here the result return to turn func, and there we decide if rollback needed or not.
		}
		default:
			cout << "Please enter a valid option!" << endl;
		}
		cout << endl;
		printBoard(boardSets); // after every choice the board is printed.
	}
}

Card* gameEngine::handToSet(Player *p, int setIndx) // here the cards move to the sets
{
	Card *c;
	char sign;
	int value;
	sign = p->isValidSign(); // checking if sign is valid
	value = p->isValidValue();// checking if value is valid
	c = p->extructCard(sign, value);
	boardSets[setIndx]->addCard(c); // returning the card to the hand
	return c;
}

int gameEngine::chooseSet(int howManySets) // the player here chose the set
{
	int indx;
	cout << "Please choose a set: ";
	indx = validInt(); // checking if iput is valid
	while (indx < 1 || indx > howManySets)
	{
		cout << "enter valid set num: ";
		cin >> indx;
	}
	return indx - 1; //index - 1, for searching in the boardset[index - 1]
}

void gameEngine::moveCards(Player *p) // moving cards between sets
{
	Card* c; // for keeping the card
	int originSetIndx, destSetIndx, value, cardIndx = -1;
	char sign;
	cout << "Old Set ->";
	originSetIndx = chooseSet(howManySets); // origin set
	
	while (boardSets[originSetIndx]->isEmpty())
	{
		cout << "this set is empty, please choose a different one" << endl;
		originSetIndx = chooseSet(howManySets); // origin set
	}

	while (cardIndx < 0)
	{
		sign = p->isValidSign(); // checking if sign is valid
		value = p->isValidValue(); // checking if value is valid
		cardIndx = boardSets[originSetIndx]->searchInSet(sign, value); // searching if this card is in the set, and returning if yes or no
	}
	c = boardSets[originSetIndx]->extructCard(sign, value); //kepping the card here to put in the other set
	cout << "New Set -> ";
	destSetIndx = chooseSet(howManySets); //destination
	boardSets[destSetIndx]->addCard(c); // the card is added to the new set
}

void gameEngine::printBoard(Set **Sets) const
{
	cout << endl << "***** Board Status *****" << endl;
	if (howManySets == 0)
		cout << endl << "No sets!" << endl << endl;
	for(int k = 0; k < howManySets; k++)
	{
		cout << "Set " << k + 1 << ": ";
		Sets[k]->printSet();
	}
	cout << endl;
}

void gameEngine::rollback(Set ** oldSets, int oldSetsNum, int oldHandNum, Player *p) // for rollback 
{
	delete[] boardSets;
	howManySets = oldSetsNum;
	boardSets = new Set*[oldSetsNum];
	for (int i = 0; i < howManySets; i++)	//rollback sets only
		boardSets[i] = oldSets[i]; //returning to the original sets
	delete[] oldSets;

	int cardIndx = oldHandNum - p->getNumberOfCards();	//saving the amount of cards the player used.
	for (int i = 0; i < cardIndx; i++)
		p->setCard(playedCards[i]);	// adding the used card back to the hand in the last place
	if (rollbackTrash) //if drew card from trash, put it back
		trash.push(p->extructCard(rollbackTrash->getSign(), rollbackTrash->getValue()));
	p->printHand();
	delete[] playedCards;	// deleting the used cards from the temp hand
}

bool gameEngine::endTurn(Player * p) //case 0, returning bool, and then goes to turn.
{
	int i;
	for (i = 0; i < howManySets; i++)
	{
		boardSets[i]->sortSet(); // sorting sets before checking if they valid.
		if (!boardSets[i]->isValidset()) //checking if the sets are valid
			return false; // if not valid return falsh
	}
	return true; // if valit return true
}

bool gameEngine::turn(Player & p)
{
	playerTurn++;	//pointing to next player
	
	int oldHandNum = p.getNumberOfCards() + 1; //saving the amount of cards in player hand, for later use.
	cout << endl << "************ Player " << p.getName() << " turn ***********" << endl << endl;
	printBoard(boardSets);
	p.printHand();
	cout << "top of trash pile is: ";
	Card *topTrash; // temp for top trash card to push/pop
	topTrash = trash.pop(); 
	topTrash->printCard(); 
	trash.push(topTrash); 
	cout << endl;

	if (!drawing(p))	//if false -> the player quit
	{
		playerTurn--;	//next player index decreased
		if (howManyPlayers == 1) // if there is one player left he won
			return false;
		else
			return true;
	}
	
	int oldSetsNum = howManySets; 
	Set **setsCopy(boardSets); //saving the sets to use in rollback if needed
	setsCopy = new Set*[howManySets];
	for (int i = 0; i < howManySets; i++)
		setsCopy[i] = new Set(*boardSets[i]);

	if (!options(p)) // if return false, illegal move -> rollback
	{
		cout << "Your move was illegal, you lost your turn!" << endl << endl;
		rollback(setsCopy, oldSetsNum, oldHandNum, &p); 
		return true; // the player lost his turn
	}
	else
	{
		delete[] setsCopy; //no rollback, delete the temp set
		if (p.getNumberOfCards() > 0) //winner check, else throw to trash
		{
			char sign;
			int value;
			p.printHand();
			cout << "Choose card to throw to trash pile ->  " << endl;
			sign = p.isValidSign();	// checking if sign is valid
			value = p.isValidValue();	// checking if value is valid
			trash.push(p.extructCard(sign, value)); // pushing card to trash
			if (p.getNumberOfCards() > 0)	//winner check
				return true;
		}
		return false; // winner
	}
}

gameEngine::~gameEngine() //destructor
{
	cout << "Destructor is on!" << endl;
	for (int i = 0; i < howManyPlayers; i++)
		players[i]->~Player();
	delete[] players;
	for (int i = 0; i < howManySets; i++)
		boardSets[i]->~Set();
	delete[] boardSets;
}

#endif // !__gameengine_p