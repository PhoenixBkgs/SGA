//	BLACK JACK
//	Author : Eugene Kim aka Komastar


#include "stdafx.h"

#define DEBUG

enum E_SHAPE	{ SPADE = 0, DIA, HEART, CLUB };
enum E_ROLE		{ DEALER = 0, PLAYER };
enum E_ACTION	{ HIT = 0, STAY, SPLIT };

#define MAX_COUNT 52

/*---------------------------------------------
Structures
---------------------------------------------*/
//	CARD
/*
SHAPE(enum->string) / NUMBER(int->string)
*/
struct tagCard
{
	E_SHAPE Shape;
	int Number;
	bool IsUse;
};

//	Deck
/*
stCARD(array or list)
*/
struct tagDeck
{
	vector<tagCard> Cards;
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
	tagDeck PlayerDeck;
};

/*---------------------------------------------
Functions
---------------------------------------------*/
//	Common functions
void ExchangeCard(tagDeck* Deck, int KeyIdx, int ShuffleIdx);
string EShapeToString(E_SHAPE Shape);
string CardNumToString(int CardNum);

//	Prepare for play
tagDeck SetupGameTable();
tagDeck CreateDeck();
void ShuffleDeck_Yates(tagDeck* Deck);
void PrintCards(tagCard* Cards);
void PrintDeck(tagDeck* Deck);
void InitPlayer(tagPlayer* Player);

//	In game
bool HitCard(tagPlayer* Player, tagDeck* Deck);
tagCard DrawCard(tagDeck* Deck);

//	End play
int CheckScore(tagCard* Cards);
tagPlayer FindWinner(tagPlayer* Player);

//	Global Vars
const string szSpade	= "♠";
const string szDia		= "◆";
const string szHeart	= "♥";
const string szClub		= "♣";

int main()
{
	//	VECTOR EXAMPLE
	/*
	vector<int> vecInt;
	vector<int>::iterator iter;

	vecInt.push_back(1);
	vecInt.push_back(3);
	vecInt.push_back(5);
	cout << vecInt[0] << endl;

	cout << vecInt.size() << endl;
	vecInt.pop_back();	//	last value pop out
	cout << vecInt.size() << endl;

	cout << *(vecInt.begin() + 1) << endl;

	for (iter = vecInt.begin(); iter != vecInt.end(); iter++)
	{
		cout << *iter << endl;
	}
	*/

	tagPlayer stDealer;
	tagPlayer stPlayer;

	tagDeck stDeck;
	stDeck = SetupGameTable();
	PrintDeck(&stDeck);

	//	main loop for game
	int curTurn = 0;
	while (true)
	{
 		curTurn++;
		//	clear console
		system("cls");
		
		cout << "HIT THE CARD !!!" << endl;
		cout << "TURN : " << curTurn << endl;

		tagCard tmpCard = DrawCard(&stDeck);
		cout << EShapeToString(tmpCard.Shape) << CardNumToString(tmpCard.Number) << endl;
		stPlayer.PlayerDeck.Cards.push_back(tmpCard);

		/*
		HitCard(&stPlayer, &stDeck);
		PrintDeck(&stPlayer.PlayerDeck);
		*/
	}

    return 0;
}

//	Initialize game table
tagDeck SetupGameTable()
{
	tagDeck tempDeck;
	tempDeck = CreateDeck();
	ShuffleDeck_Yates(&tempDeck);

	return tempDeck;
}

//	no use
void InitPlayer(tagPlayer* Player)
{
	
}

//	Create Deck
/*
number 1 to 13
shape E_SHAPE
*/
tagDeck CreateDeck()
{
	tagDeck deck;

	for (int j = 0; j < 4; j++)			//	SHAPE
	{
		for (int k = 1; k < 14; k++)	//	NUMBER
		{
			tagCard card = { (E_SHAPE)j, k, false };
			deck.Cards.push_back(card);
		}
	}

	return deck;
}

//	Shuffle by Yates algorithm
void ShuffleDeck_Yates(tagDeck* Deck)
{
	for (int i = 0; i < MAX_COUNT; i++)
	{
		srand(time(0));
		int shuffleIdx = rand() % MAX_COUNT;
		ExchangeCard(Deck, i, shuffleIdx);
	}
}

//	Exchange KeyIdx between ShuffleIdx
void ExchangeCard(tagDeck* Deck, int KeyIdx, int ShuffleIdx)
{
	tagCard shuffleTemp;
	shuffleTemp = Deck->Cards[KeyIdx];
	Deck->Cards[KeyIdx] = Deck->Cards[ShuffleIdx];
	Deck->Cards[ShuffleIdx] = shuffleTemp;
}

//	Print entire deck info
void PrintDeck(tagDeck* Deck)
{
	vector<tagCard>::iterator iter;
	for (iter = Deck->Cards.begin(); iter != Deck->Cards.end(); ++iter)
	{
		string shape = EShapeToString(iter->Shape);
		string number = CardNumToString(iter->Number);

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
		retShape = szSpade;
		break;
	case DIA:
		retShape = szDia;
		break;
	case HEART:
		retShape = szHeart;
		break;
	case CLUB:
		retShape = szClub;
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


//	IN GAME FUNCTIONS
bool HitCard(tagPlayer* Player, tagDeck* Deck)
{
	bool isCardRemain = false;
	tagCard* drawCard = new tagCard;
	for (int i = 0; i < MAX_COUNT; i++)
	{
		//	find new card
		if (Deck->Cards[i].IsUse == false)
		{
			drawCard = &Deck->Cards[i];
			Deck->Cards[i].IsUse = true;
			isCardRemain = true;
			break;
		}
		else
		{
			//	do nothing
		}
	}

	for (int i = 0; i < MAX_COUNT; i++)
	{
		tagCard* tempCard = &Player->PlayerDeck.Cards[i];
		if (tempCard->IsUse == false)
		{
			tempCard = drawCard;
			tempCard->IsUse = true;
			break;
		}
	}

	return true;
}

tagCard DrawCard(tagDeck* Deck)
{
	//	사용안한 첫번째 카드 찾기
	//	찾은 카드 반환
	//	루프 종료
	tagCard retCard;
	int drawIdx = Deck->Cards.size() - 1;

	retCard = Deck->Cards[drawIdx];
	Deck->Cards.pop_back();

	return retCard;
}

//	END PLAY FUNCTIONS
//	check card number
int CheckScore(tagCard* Cards)
{
	int score = 0;
	tagCard tempCards[MAX_COUNT];
	//	카드 정렬(내림차순, JQK = 10)
	//	정렬된 숫자의 합이 10이상일 경우
	//	A = 1
	//	정렬된 숫자의 합이 10미만일 경우
	//	A = 11
	//	JQK + A = 블랙잭
	//	블랙잭 반환 = 0

	return score;
}

//	
tagPlayer FindWinner(tagPlayer* Player)
{
	tagPlayer retPlayer;
	return retPlayer;
}