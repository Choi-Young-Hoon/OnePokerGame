#include "game/PokerCard.hpp"
#include "util/GameType.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace ONEPOKER;

string CheckWinMessage(enum GAME flag){
	switch(flag){
		case GAME::LOSE: return "LOSE";
		case GAME::WIN: return "WIN";
		case GAME::DRAW: return "DRAW";
	}
	return "";
}

void PrintLine(){
	cout << "--------------------------------------" << endl;
}
int main(void){
	PokerCard card_1, card_2;

	PrintLine();
	cout << "Card_1 Flag : DOWN, CARD_3, NON" <<endl;
	card_1.SetCard(CARD_TYPE::CARD_DOWN, CARD::CARD_3, CARD::CARD_NON);
	cout << "Card_2 Flag : DOWN, CARD_4, NON" << endl;
	card_2.SetCard(CARD_TYPE::CARD_DOWN, CARD::CARD_4, CARD::CARD_NON);
	cout << "Check Card_1.CheckWin(Card_2) : " 
		<< CheckWinMessage(card_1.CheckWin(card_2)) << endl; 

	PrintLine();
	cout << "Card_1 Flag : DOWN, CARD_2, CARD_A" << endl;
	card_1.SetCard(CARD_TYPE::CARD_DOWN, CARD::CARD_2, CARD::CARD_A);
	cout << "Card_2 Flag : UP, CARD_A, NON" << endl;
	card_2.SetCard(CARD_TYPE::CARD_UP, CARD::CARD_A, CARD::CARD_NON);
	cout << "Check Card_1.CheckWin(Card_2) : "
		<< CheckWinMessage(card_1.CheckWin(card_2)) << endl;

	PrintLine();
	cout << "Card_1 Flag : DOWN, CARD_3, NON" << endl;
	card_1.SetCard(CARD_TYPE::CARD_DOWN, CARD::CARD_3, CARD::CARD_NON);
	cout << "Card_2 Flag : DOWN, CARD_3, NON" << endl;
	card_2.SetCard(CARD_TYPE::CARD_DOWN, CARD::CARD_3, CARD::CARD_NON);
	cout << "Check Card_1.CheckWin(Card_2) : "
		<< CheckWinMessage(card_1.CheckWin(card_2)) << endl;

	PrintLine();
	cout << "card_1.IsOpen() : " << card_1.IsOpen() << endl;
	card_1.SetOpenCard();
	cout << "card_1.SetOpenCard() after : " << card_1.IsOpen() << endl;
	return 0;
}
