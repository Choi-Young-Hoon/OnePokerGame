#include "game/PokerCard.hpp"
#include "game/PokerUser.hpp"
#include "util/GameType.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace ONEPOKER;
int main(void){
	PokerUser user;
	PokerCard card;
	PokerCard * pCard;
	cout << "Fist card Flag : DOWN, CARD_5, NON" << endl;
	card.SetCard(CARD_TYPE::CARD_DOWN, CARD::CARD_5, CARD::CARD_NON);
	cout << "Fist card Add result : " << user.AddCard(card) << endl;

	cout << "Second card Flag : UP, CARD_J, NON" << endl;
	card.SetCard(CARD_TYPE::CARD_UP, CARD::CARD_J, CARD::CARD_NON);
	cout << "Second card Add result : " << user.AddCard(card) << endl;

	cout << "Third card Flag : UP, CARD_10, NON" << endl;
	card.SetCard(CARD_TYPE::CARD_UP, CARD::CARD_10, CARD::CARD_NON);
	cout << "Third card Add result : " << user.AddCard(card) << endl;

	cout << "Second card Set open" << endl;
	user.SetOpenCard(CARD_INDEX::CARD_SECOND);
	
	cout << "Second card Get" << endl;
	pCard = user.GetCard(CARD_INDEX::CARD_SECOND);
	cout << "Second card Open??? : " << pCard->IsOpen() << endl;

	return 0;
}
