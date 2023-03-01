# Rummy---cpp-Project
A game of Rummy buily in cpp

This was a the 2nd class project in the 2nd year in computer engineering.

Rummy is a multi player (2-7 players) card game where each player tries to create and complete sets of cards.
The goal of the game is to be the first player to finish all your cards.
The game has a stack that includs two decks of standart playing cards (4 sets with 13 values).
At the start of the game the cards are shuffled and each player draws 14 cards, then another cards is drawn and placed in the board as the start of the trash stack.

In his (or hers) respective turn, a player can quit the game, draw the first card from the trash stack or draw a card from the deck, then he can add new sets, add cards to new sets or rearrange the sets on the board so he can play.
At the end of his turn, if the all the sets on the board are legal, a player must throw a card to the trash stack.
If there is an illegal set on the board the game rollbacks to its original state.

A set must be at least 3 cards.

A legal set must be one of the following:

1. An increasing series of cards from the same set (for example: 2,3,4 of diamond).

2. A series of cards with the same value but from different sets (2 of diamond, clubs and hearts).

project structure:

![structure](https://user-images.githubusercontent.com/102590409/222125717-34b66d16-7266-4a4f-9725-a9d98e1d8ebc.jpg)

