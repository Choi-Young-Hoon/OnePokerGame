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
		PokerUser():open_card_index(CARD_INDEX::CARD_NON_SELECT){}
		~PokerUser(){}
		
		inline void SetUserData(UserData data){ my_data = data; }
		inline void SetOpenCard(enum CARD_INDEX index){
			card_list[index].SetOpenCard();
			open_card_index = index;
		}
		inline bool AddCard(const PokerCard & card){
			if(OnePokerDefault::MAX_CARD <= card_list.size())
				return false;
			card_list.push_back(card);
			return true;
		}
		inline UserData * GetUserData(){ return &my_data; }
		inline PokerCard * GetOpenCard(){
			if(open_card_index != CARD_INDEX::CARD_NON_SELECT)
				return &card_list[open_card_index];
			return NULL;
		}
		inline PokerCard * GetCard(enum CARD_INDEX index){
			if(index < card_list.size())
				return &card_list[index];
			return NULL;
		}
		inline void CardClear(){
			card_list.clear();
			open_card_index = CARD_INDEX::CARD_NON_SELECT;
		}
	private:
		vector<PokerCard> card_list;
		enum CARD_INDEX open_card_index;
		UserData my_data;
	};
};
#endif
