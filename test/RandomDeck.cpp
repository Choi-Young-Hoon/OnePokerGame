#include "game/CardGame.hpp"
#include "db/DataBase.hpp"
#include "db/GameSetting.hpp"
#include <iostream>
#include <queue>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace CARDGAME;

string WhatIsThis(int type);
string WhatIsThis(enum CARD card);

int main(void){
	if(DataBase::Connect("127.0.0.1", "root", "950214") 
			== OP_ERROR_FLAG::DB_CONNECT_ERROR)
		return -1;

	CardDataMapInit();
	
	srand(time(NULL));
	
	CardList * card_list_instance = CardList::GetInstance();
	card_list_instance->GetData();
	card_list_instance->GetCardList();

	CardGame * card_game = SelectGameMode(GAME_MODE::GAME_ONEPOKER);
	
	queue<PokerCard> card_deck = card_game->GetRandomMixDeck(
					card_list_instance->GetCardList(),
					CARD_DECK::DECK_UP_DOWN);

	int counter = 0;
	while(!card_deck.empty()){
		PokerCard & iter = card_deck.front();
		cout << WhatIsThis(iter.GetName());
		card_deck.pop();
		counter++;
		if(counter % 3 == 0)
			cout << endl;
		else
			cout << "\t";
	}
	cout << "개수 : " << counter << endl;


	return 0;
}

string WhatIsThis(int type){
	switch(type){
		case 0: return "CARD_NON_TYPE";
		case 1: return "CARD_DOWN";
		case 2: return "CARD_UP";
	}
	return "";
}
string WhatIsThis(enum CARD card){
	switch(card){
		case CARD_NON: return "CARD_NON";
		case CARD_2: return "CARD_2";
		case CARD_3: return "CARD_3";
		case CARD_4: return "CARD_4";
		case CARD_5: return "CARD_5";
		case CARD_6: return "CARD_6";
		case CARD_7: return "CARD_7";
		case CARD_8: return "CARD_8";
		case CARD_9: return "CARD_9";
		case CARD_10: return "CARD_10";
		case CARD_K: return "CARD_K";
		case CARD_Q: return "CARD_Q";
		case CARD_J: return "CARD_J";
		case CARD_A: return "CARD_A";
	}
	return "";
}
