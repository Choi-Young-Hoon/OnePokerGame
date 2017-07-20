#ifndef __ONEPOKER_GAME_POKERUSER_HEADER__
#define __ONEPOKER_GAME_POKERUSER_HEADER__
#include "db/User.hpp"
#include "game/OnePokerDefault.hpp"
#include "game/PokerCard.hpp"
#include "util/GameType.hpp"
#include <iostream>
#include <vector>
using namespace std;

namespace ONEPOKER{
	class PokerUser : public OnePokerDefault {
	public:
		PokerUser():openCardIndex(CARD_INDEX::CARD_NON_SELECT){}
		~PokerUser(){}
		
		inline void setUserData(UserData data){ myData = data; }
		inline void setOpenCard(enum CARD_INDEX index){
			cardList[index].setOpenCard();
			openCardIndex = index;
		}
		inline bool addCard(const PokerCard & card){
			if(OnePokerDefault::MAX_CARD <= cardList.size())
				return false;
			cardList.push_back(card);
			return true;
		}
		inline UserData * getUserData(){ return &myData; }
		inline PokerCard * getOpenCard(){
			if(openCardIndex != CARD_INDEX::CARD_NON_SELECT)
				return &cardList[openCardIndex];
			return NULL;
		}
		inline PokerCard * getCard(enum CARD_INDEX index){
			if(index < cardList.size())
				return &cardList[index];
			return NULL;
		}
	private:
		vector<PokerCard> cardList;
		enum CARD_INDEX openCardIndex;
		UserData myData;
	};
};
#endif
