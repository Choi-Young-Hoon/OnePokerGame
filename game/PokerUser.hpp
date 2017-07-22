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
		
		/*
		 * 유저 정보를 저장
		 */
		inline void SetUserData(UserData data){ my_data = data; }

		//Open 카드 지정.
		inline void SetOpenCard(enum CARD_INDEX index){
			card_list[index].SetOpenCard();
			open_card_index = index;
		}

		/*
		 * 카드 추가
		 * @return
		 * 추가 성공시 - true
		 * 이미 최대 카드수를 가지고 있으면 - false
		 */
		inline bool AddCard(const PokerCard & card){
#ifdef ONEPOKER_DEBUG
			cout << "AddCard card_list.size() : " << card_list.size() << endl;
#endif
			if(OnePokerDefault::MAX_CARD <= card_list.size())
				return false;
			card_list.push_back(card);
			return true;
		}
		
		inline UserData * GetUserData(){ return &my_data; }

		//is_open 플래그가 true 로 설정된 카드를 반환한다.
		inline PokerCard * GetOpenCard(){
			if(open_card_index != CARD_INDEX::CARD_NON_SELECT)
				return &card_list[open_card_index];
			return NULL;
		}
		//특정 카드를 반환한다.
		inline PokerCard * GetCard(enum CARD_INDEX index){
			if(index < card_list.size())
				return &card_list[index];
			return NULL;
		}

		//내부 카드 정보를 초기화한다.
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
