//	BLACK JACK
//	Author : Eugene Kim aka Komastar


#include "stdafx.h"

#define DEBUG

enum E_SHAPE	{ SPADE = 0, DIA, HEART, CLUB };
enum E_ROLE		{ DEALER = 0, PLAYER, DRAW, NONE };
enum E_ACTION	{ HIT = 1, STAY, SPLIT, GAMEEND, NOACT };

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
	bool IsHidden;
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
void PrintDeck(tagDeck* Deck);
void PrintCard(tagCard tagCard);
void BubbleSort(tagDeck* Deck, bool IsIncrease);

//	Prepare for play
tagDeck SetupGameTable();
void InitDeck(tagDeck* Deck);
void InitPlayersDeck(tagPlayer* Dealer, tagPlayer* Player);
tagDeck CreateDeck();
void ShuffleDeck_Yates(tagDeck* Deck);
void InitPlayer(tagPlayer* Player);

//	In game
//	bool HitCard(tagPlayer* Player, tagDeck* Deck);
tagCard DrawCard(tagDeck* Deck);
E_ACTION ShowInterface(tagPlayer Dealer, tagPlayer Player, bool IgnoreInput);

//	End play
int CheckScore(tagDeck* Deck);
E_ROLE FindWinner(tagPlayer* Dealer, tagPlayer* Player);

//	Global Vars
const string szSpade	= "♠";
const string szDia		= "◆";
const string szHeart	= "♥";
const string szClub		= "♣";

int bettingMoney = 100;
int buriedMoney = 0;

int main()
{
	tagPlayer stDealer;
	tagPlayer stPlayer;
	tagDeck stDeck;
	stDeck = SetupGameTable();
	stDealer.Role = DEALER;
	stPlayer.Budget = 10000;
	stPlayer.Role = PLAYER;

	bool IsStart = true;
	bool IsRestart = false;
	bool IsGameEnd = false;
	bool IsDealerTurn = false;

	//	main loop for game
	int curTurn = 0;
	while (true)
	{
 		curTurn++;
		if (IsStart)
		{
			tagCard tmpCard = DrawCard(&stDeck);
			stDealer.PlayerDeck.Cards.push_back(tmpCard);

			tmpCard = DrawCard(&stDeck);
			stPlayer.PlayerDeck.Cards.push_back(tmpCard);

			tmpCard = DrawCard(&stDeck);
			tmpCard.IsHidden = true;
			stDealer.PlayerDeck.Cards.push_back(tmpCard);

			tmpCard = DrawCard(&stDeck);
			stPlayer.PlayerDeck.Cards.push_back(tmpCard);

			IsStart = false;
		}
		
		E_ACTION actionInput = ShowInterface(stDealer, stPlayer, false);
		E_ROLE winner = NONE;
		int playerScore = 0;
		switch (actionInput)
		{
		case HIT:
			//	Draw Card
			stPlayer.PlayerDeck.Cards.push_back(DrawCard(&stDeck));
			playerScore = CheckScore(&stPlayer.PlayerDeck);
			if (playerScore > 21)
			{
				//	BURST
				winner = DEALER;
				IsRestart = true;
				stDealer.PlayerDeck.Cards[1].IsHidden = false;
				ShowInterface(stDealer, stPlayer, true);
				break;
			}
			IsDealerTurn = false;
			break;
		case STAY:
			//	Now Dealer has turn
			IsDealerTurn = true;
			break;
			/*
		case SPLIT:
			break;
			*/
		case GAMEEND:
			for (int i = 0; i < 100; i++)
			{
				Sleep(10);
				cout << "GAME OVER !!!" << endl;
			}
			Sleep(1000);
			IsGameEnd = true;
		default:
			break;
		}

		//	DEALER TURN
		while (IsDealerTurn)
		{
			stDealer.PlayerDeck.Cards[1].IsHidden = false;
			ShowInterface(stDealer, stPlayer, true);
			int dealerScore = CheckScore(&stDealer.PlayerDeck);
			//	17 미만. 딜러 HIT
			if (dealerScore < 17)
			{
				stDealer.PlayerDeck.Cards.push_back(DrawCard(&stDeck));
			}
			else
			{
				//	딜러 STAY
				winner = FindWinner(&stDealer, &stPlayer);
				IsRestart = true;
				break;
			}
		}

		switch (winner)
		{
		case DEALER:
			cout << "DEALER WIN !!!" << endl;
			Sleep(1000);
			break;
		case PLAYER:
			cout << "PLAYER WIN !!!" << endl;
			Sleep(1000);
			break;
		case DRAW:
			cout << "DRAW !!!" << endl;
			Sleep(1000);
			break;
		case NONE:
		default:
			break;
		}

		//	게임 재시작
		if (IsRestart)
		{
			//	Dealer Turn
			//	Reset table
			InitDeck(&stDeck);
			InitPlayersDeck(&stDealer, &stPlayer);
			stDeck = SetupGameTable();
			IsStart = true;
			IsRestart = false;
		}

		//	게임 종료
		if (IsGameEnd)
		{
			return 0;
		}

		Sleep(500);
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

void InitDeck(tagDeck* Deck)
{
	int deckSize = Deck->Cards.size();
	for (int i = 0; i < deckSize; i++)
	{
		Deck->Cards.pop_back();
	}
}

void InitPlayersDeck(tagPlayer* Dealer, tagPlayer* Player)
{
	InitDeck(&Dealer->PlayerDeck);
	InitDeck(&Player->PlayerDeck);
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
		PrintCard(*iter);
	}
}

void PrintCard(tagCard tagCard)
{
	string shape = EShapeToString(tagCard.Shape);
	string number = CardNumToString(tagCard.Number);

	cout << shape << number;
}

void BubbleSort(tagDeck* Deck, bool IsIncrease)
{
	bool isExchange = false;

	int lenDeck = Deck->Cards.size() - 1;
	for (int i = 0; i < lenDeck; i++)
	{
		for (int j = 1; j < lenDeck - (i + 1); j++)
		{
			if (IsIncrease)
			{
				if (Deck->Cards[j - 1].Number > Deck->Cards[j].Number)
				{
					//	switch data
					tagCard temp = Deck->Cards[j - 1];
					Deck->Cards[j - 1] = Deck->Cards[j];
					Deck->Cards[j] = temp;

					isExchange = true;
				}
			}
			else
			{
				if (Deck->Cards[j - 1].Number < Deck->Cards[j].Number)
				{
					//	switch data
					tagCard temp = Deck->Cards[j - 1];
					Deck->Cards[j - 1] = Deck->Cards[j];
					Deck->Cards[j] = temp;

					isExchange = true;
				}
			}
		}

		if (!isExchange)
		{
			break;
		}
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
/*
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
*/

//	Draw card from deck
tagCard DrawCard(tagDeck* Deck)
{
	//	사용안한 첫번째 카드 찾기
	//	찾은 카드 반환
	//	루프 종료
	tagCard retCard;
	int drawIdx = Deck->Cards.size() - 1;

	retCard = Deck->Cards[rand() % drawIdx];
	Deck->Cards.pop_back();

	return retCard;
}

//	Show game interface
E_ACTION ShowInterface(tagPlayer Dealer, tagPlayer Player, bool IgnoreInput)
{
	//	screen clear
	system("cls");

	//	보유 금액
	cout << "$ : " << Player.Budget << endl;

	//	딜러 이름
	cout << "------------------------------------------------------------------" << endl;
	cout << "-------------------------DEALER-----------------------------------" << endl;
	//	딜러 카드1 / 카드2 (???)
	vector<tagCard>::iterator iter;
	for (iter = Dealer.PlayerDeck.Cards.begin(); iter  != Dealer.PlayerDeck.Cards.end(); ++iter)
	{
		if (iter->IsHidden)
		{
			cout << "???";
		}
		else
		{
			PrintCard(*iter);
		}
		cout << "\t";
	}
	cout << endl;
	//-------------------------------------
	//	플레이어 이름

	cout << "------------------------------------------------------------------" << endl;
	cout << "-------------------------PLAYER-----------------------------------" << endl;
	//	플레이어 카드1 / 카드2 / ...
	for (iter = Player.PlayerDeck.Cards.begin(); iter != Player.PlayerDeck.Cards.end(); ++iter)
	{
		PrintCard(*iter);
		cout << "\t";
	}
	cout << endl;
	cout << "------------------------------------------------------------------" << endl;
	//-------------------------------------
	//	명령 입력. 1.힛  2.스테이
	cout << "명령 선택(1.Hit / 2.Stay): " << endl;
	int input = 0;
	if (IgnoreInput)
	{
		input = 5;
	}
	else
	{
		cin >> input;
	}
	return (E_ACTION)input;
}


//	END PLAY FUNCTIONS
//	check card number
int CheckScore(tagDeck* Deck)
{
	int score = 0;
	int tempScore = 0;
	int deckSize = 0;
	bool IsJQK = false;
	//	카드 정렬(내림차순, JQK = 10)
	BubbleSort(Deck, false);

	//	카드 숫자의 합
	deckSize = Deck->Cards.size();
	for (int i = 0; i < deckSize; i++)
	{
		int cardNum = Deck->Cards[i].Number;
		if (cardNum > 10)	//	JQK 처리
		{
			cardNum = 10;
			IsJQK = true;
		}
		tempScore += cardNum;
	}

	//	JQK + A = 블랙잭
	//	블랙잭 반환 = -1
	//	받은 카드 2장 && A + JQK)
	if (deckSize == 2 && tempScore == 11 && IsJQK)
	{
		score = -1;
	}
	
	//	정렬된 숫자의 합이 10이상일 경우
	//	A = 1
	if (tempScore > 10)
	{
		score = tempScore;
	}

	//	정렬된 숫자의 합이 10미만일 경우
	//	A = 11
	if (tempScore < 10)
	{
		//	함수로 뺄 수 있음
		for (int i = 0; i < deckSize; i++)
		{
			int cardNum = Deck->Cards[i].Number;
			if (cardNum > 10)	//	JQK 처리
			{
				cardNum = 10;
				IsJQK = true;
			}

			if (cardNum == 1)
			{
				cardNum = 10;
			}
			tempScore += cardNum;
		}

		score = tempScore;
	}

	return score;
}

//	
E_ROLE FindWinner(tagPlayer* Dealer, tagPlayer* Player)
{
	E_ROLE retRole = NONE;

	int dealerScore = CheckScore(&Dealer->PlayerDeck);
	int playerScore = CheckScore(&Player->PlayerDeck);

	//	다수의 플레이어가 있으면 정렬 사용해야함
	int subScore = dealerScore - playerScore;

	if (playerScore == -1)
	{
		//	블랙잭
		retRole = PLAYER;
		Player->Budget += (bettingMoney * 1.5);
		bettingMoney = 100;
	}

	//if ((subScore > 0 || playerScore > 21) && dealerScore <= 21)
	if ((dealerScore > playerScore && dealerScore <= 21) || playerScore > 21)
	{
		//	딜러 승
		retRole = DEALER;
		Player->Budget -= bettingMoney;
		bettingMoney = 100;
	}
	else if ((dealerScore < playerScore && playerScore <= 21) || dealerScore > 21)
	{
		//	플레이어 승
		retRole = PLAYER;
		Player->Budget += bettingMoney;
		bettingMoney = 100;
	}
	else
	{
		//	무승부
		bettingMoney += 100;
		retRole = DRAW;
	}

	return retRole;
}