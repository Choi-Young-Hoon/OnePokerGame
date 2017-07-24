#include "game/CardGame.hpp"
#include "game/OnePoker.hpp"
#include "db/GameSetting.hpp"

#include <list>
#include <iterator>
using namespace std;
using namespace CARDGAME;

extern "C" CardGame * SelectGameMode(enum GAME_MODE mode){
	switch(mode){
		case GAME_ONEPOKER:
			return new ONEPOKER::OnePoker();
	}
	return NULL;
}

static queue<PokerCard> RandomMix(list<PokerCard> & card_dec){
	queue<PokerCard> ret_card_deck;
	int random_index = 0;
	while(card_dec.size()){
		auto iter = card_dec.begin();
		random_index = rand() % card_dec.size();
		advance(iter, random_index);
		ret_card_deck.push(*iter);
		card_dec.erase(iter);
	}
	return ret_card_deck;
}

static inline int CheckCard(string & card){
	if(card == "A") return CARD_A;
	else if(card == "Q") return CARD_Q;
	else if(card == "J") return CARD_J;
	else if(card == "K") return CARD_K;
	return atoi(card.c_str());
}

queue<PokerCard> CardGame::GetRandomMixDeck(vector<string> & card_list, enum CARD_DECK deck_type){
	PokerCard card;
	list<PokerCard> card_deck;
	auto data = card_list.begin();
	
	int card_flag;
	int card_name;
	while(data != card_list.end()){
		card_name = CheckCard(*data);
		if(deck_type == CARD_DECK::DECK_UP_DOWN){
			if(card_name <= CARD::CARD_7)
				card_flag = (int)CARD_TYPE::CARD_DOWN;
			else
				card_flag = (int)CARD_TYPE::CARD_UP;
			//카드 4개씩 삽입
			if(card_name == 2)
				card.SetCard(card_flag, (enum CARD)card_name, CARD::CARD_A);
			else 
				card.SetCard(card_flag, (enum CARD)card_name, CARD::CARD_NON);
			for(int i = 0; i < 4; i++)
				card_deck.push_back(card);
		}
		else if(deck_type == CARD_DECK::DECK_SHAPE){
			card.SetCard(CARD_SHAPE::CARD_DIAMOND, (enum CARD)card_name, CARD::CARD_NON);
			card_deck.push_back(card);
			card.SetCard(CARD_SHAPE::CARD_HEART, (enum CARD)card_name, CARD::CARD_NON);
			card_deck.push_back(card);
			card.SetCard(CARD_SHAPE::CARD_TREECLOVER, (enum CARD)card_name, CARD::CARD_NON);
			card_deck.push_back(card);
			card.SetCard(CARD_SHAPE::CARD_SPADE, (enum CARD)card_name, CARD::CARD_NON);
			card_deck.push_back(card);
		}
		data++;
	}
	
	return RandomMix(card_deck);
}
