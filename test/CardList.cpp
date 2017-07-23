#include "db/DataBase.hpp"
#include "db/GameSetting.hpp"
#include "util/DataBaseType.hpp"
#include "util/GameType.hpp"
#include "game/PokerCard.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace CARDGAME;

string WhatIsThis(enum CARD_TYPE type){
	switch(type){
		case CARD_NON_TYPE: return "CARD_NON_TYPE";
		case CARD_DOWN: return "CARD_DOWN";
		case CARD_UP: return "CARD_UP";
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
int main(void){
	if(DataBase::Connect("127.0.0.1", "root", "950214") 
			== OP_ERROR_FLAG::DB_CONNECT_ERROR)
		return -1;
	CardDataMapInit();

	PokerCard card;
	CardList * card_list = CardList::GetInstance();
	for(int i = 0; i < 3; i++){
		cout << "Get ramdom card : " << endl;
		card_list->GetData();
		card = card_list->GetRandomCard();
	
		cout << "Card type : " << WhatIsThis(card.GetType()) << endl;
		cout << "Card name : " << WhatIsThis(card.GetName()) << endl;
		cout << "Card win : " << WhatIsThis(card.GetWinCard()) << endl;
	}
	DataBase::Close();
	return 0;
}
