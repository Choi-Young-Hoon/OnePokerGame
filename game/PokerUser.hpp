#ifndef __ONEPOKER_GAME_POKERUSER_HEADER__
#define __ONEPOKER_GAME_POKERUSER_HEADER__
#include "db/User.hpp"
#include "game/PokerCard.hpp"
#include "util/GameType.hpp"
#include <iostream>
#include <vector>
using namespace std;

namespace CARDGAME{ 
	class PokerUser {
	public:
		PokerUser(){}
		~PokerUser(){}
		
		/*
		 * 유저 정보를 저장
		 */
		inline void SetUserData(UserData data){ my_data = data; }

		//Open 카드 지정.
		inline void SetOpenCard(int index){
			card_list[index].SetOpenCard();
		}

		/*
		 * 카드 추가
		 * @return
		 * 추가 성공시 - true
		 * 이미 최대 카드수를 가지고 있으면 - false
		 */
		inline void AddCard(const PokerCard & card){
			card_list.push_back(card);
		}
		
		inline UserData * GetUserData(){ return &my_data; }

		//is_open 플래그가 true 로 설정된 카드를 반환한다.
		inline vector<PokerCard>  GetOpenCard(){
			vector<PokerCard> open_card_list;
			for(auto & iter : card_list){
				if(iter.IsOpen())
					open_card_list.push_back(iter);
			}
			return open_card_list;
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
		}

		//카드 개수 반환
		inline int GetCardCount(){
			return card_list.size();
		}
	private:
		vector<PokerCard> card_list;
		UserData my_data;
	};
};
#endif
