//	BLACK JACK
//	Author : Eugene Kim aka Komastar

#define DEBUG

#include "stdafx.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

enum E_SHAPE { SPADE = 0, DIA, HEART, CLUB };
enum E_ROLE { DEALER = 0, PLAYER };

#define MAX_COUNT 52

/*---------------------------------------------
Structures
---------------------------------------------*/
//	CARD
/*
SHAPE(char) / NUMBER(int)
*/
struct tagCard
{
	E_SHAPE Shape;
	int Number;
};

//	Deck
/*
stCARD(array or list)
*/
struct tagDeck
{
	tagCard Cards[MAX_COUNT];
};

//	Player
/*
Player Name / Budget / stCARD(array or list)
*/
struct tagPlayer
{
	string Name;
	int Budget;
	E_ROLE Role;
	tagCard Cards[];
};

/*---------------------------------------------
Functions
---------------------------------------------*/
string EShapeToString(E_SHAPE Shape);
string CardNumToString(int CardNum);
void CreateDeck(tagCard* Deck);
tagDeck CreateDeck();
void ShuffleDeck(tagDeck* Deck, int LoopCnt);
void PrintDeck(tagCard* Deck);

int main()
{
	tagDeck deck = CreateDeck();
	ShuffleDeck(&deck, 1000);
	PrintDeck(deck.Cards);

    return 0;
}

tagDeck CreateDeck()
{
	int totalCnt = 0;
	tagDeck deck;

	for (int j = 0; j < 4; j++)			//	SHAPE
	{
		for (int k = 1; k < 14; k++)	//	NUMBER
		{
			tagCard card = { (E_SHAPE)j, k };
			deck.Cards[totalCnt] = card;
			totalCnt++;
		}
	}

	return deck;
}

void ShuffleDeck(tagDeck* Deck, int LoopCnt)
{
	for (int i = 0; i < LoopCnt; i++)
	{
		this_thread::sleep_for(chrono::milliseconds(2));
		srand(time(0));

		int shuffleIdx1 = rand() % 26;
		int shuffleIdx2 = 0;
		
		this_thread::sleep_for(chrono::milliseconds(2));
		srand(time(0));
		
		shuffleIdx2 = rand() % 26;
		shuffleIdx2 += 26;

		tagCard shuffleTemp;
		shuffleTemp = Deck->Cards[shuffleIdx1];
		Deck->Cards[shuffleIdx1] = Deck->Cards[shuffleIdx2];
		Deck->Cards[shuffleIdx2] = shuffleTemp;
	}
}

void PrintDeck(tagCard* Cards)
{
	for (int i = 0; i < MAX_COUNT; i++)
	{
		string shape = EShapeToString(Cards[i].Shape);
		string number = CardNumToString(Cards[i].Number);

		cout << shape << number << endl;
	}	
}

//	SPADE	♠
//	DIA		◆
//	HEART	♥
//	CLUB	♣
string EShapeToString(E_SHAPE Shape)
{
	string retShape = "";
	switch (Shape)
	{
	case SPADE:
		retShape = "♠";
		break;
	case DIA:
		retShape = "◆";
		break;
	case HEART:
		retShape = "♥";
		break;
	case CLUB:
		retShape = "♣";
		break;
	default:
		//	do nothing
		break;
	}

	return retShape;
}

string CardNumToString(int CardNum)
{
	string retResult;
	switch (CardNum)
	{
	case 1:
		retResult = "A";
		break;
	case 11:
		retResult = "J";
		break;
	case 12:
		retResult = "Q";
		break;
	case 13:
		retResult = "K";
		break;
	default:
		retResult = to_string(CardNum);
		break;
	}

	return retResult;
}