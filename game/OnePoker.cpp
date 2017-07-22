#include "game/OnePoker.hpp"
#include "util/GameType.hpp"
#include "db/User.hpp"

#ifdef ONEPOKER_DEBUG
#include <iostream>
#endif

using namespace std;
using namespace ONEPOKER;

#ifdef ONEPOKER_DEBUG
static void ShowCard(PokerCard*);
#endif

enum PLAYER OnePoker::CheckWinner(){
	PokerCard * player1_card = player_list[PLAYER::PLAYER_1].GetOpenCard();
	PokerCard * player2_card = player_list[PLAYER::PLAYER_2].GetOpenCard();

	switch(player1_card->CheckWin(*player2_card)){
		case GAME::WIN: 
			return PLAYER::PLAYER_1;
		case GAME::LOSE: 
			return PLAYER::PLAYER_2;
		case GAME::DRAW:
			return PLAYER::PLAYER_NON;
	}
	return PLAYER::PLAYER_NON;
}

bool OnePoker::GetRandomCard(){
	PokerCard card;

	for(int player_num = 0; player_num < OnePokerDefault::MAX_USER; player_num++){
		for(int card_num = 0; card_num < OnePokerDefault::MAX_CARD; card_num++){
			card = card_list->GetRandomCard();
#ifdef ONEPOKER_DEBUG
			ShowCard(&card);
#endif
			if(!player_list[player_num].AddCard(card))
				return false;
		}
	}
	return true;
}

#ifdef ONEPOKER_DEBUG

static string WhatIsThisCard(enum CARD_TYPE type){
	switch(type){
		case CARD_NON_TYPE: return "CARD_NON_TYPE";
		case CARD_DOWN: return "CARD_DOWN";
		case CARD_UP: return "CARD_UP";
	}
	return "";
}

static string WhatIsThisCard(enum CARD card){
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

static void ShowCard(PokerCard * card){
	cout << "Card type : " << WhatIsThisCard(card->GetType()) << endl;
	cout << "Card name : " << WhatIsThisCard(card->GetName()) << endl;
	cout << "Card win : " << WhatIsThisCard(card->GetWinCard()) << endl;
}
#endif
