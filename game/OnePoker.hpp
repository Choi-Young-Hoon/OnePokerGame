#ifndef __ONEPOKER_GAME_ONEPOKER__HEADER__
#define __ONEPOKER_GAME_ONEPOKER__HEADER__

#ifndef __ONEPOKER_DB_GAMESETTING_HEADER__
#include "db/GameSetting.hpp"
#endif

#include "game/PokerUser.hpp"
#include "game/OnePokerDefault.hpp"
#include "util/GameType.hpp"
#include <iostream>
#include <vector>
using namespace std;

namespace ONEPOKER{
	class OnePoker : public OnePokerDefault{
	public:
		OnePoker():stage_money(0){
			card_list = CardList::GetInstance();
			card_list->GetData();
		}
		OnePoker(PokerUser player1, PokerUser player2)
			:stage_money(0){
				player_list.push_back(player1);
				player_list.push_back(player2);
		}
		
		//이긴 유저 번호를 번환
		enum PLAYER CheckWinner();

		//내부에 설정된 유저에게 랜덤하게 카드를 발급
		bool GetRandomCard();
		

		//게임이 끝나 종료 작업
		void GameFinish();
		
		//특정 유저의 판돈 배팅
		inline void Betting(enum PLAYER player, int betting_money){
			player_betting[player] += betting_money;
		}

		//특정 유저의 PokerUser 객체를 반환한다.
		inline PokerUser * GetUser(enum PLAYER player){
			if((player >= OnePokerDefault::MAX_USER) && 
			   (player >= player_list.size()))
				return NULL;
			return &player_list[player];
		}

		//특정 유저의 카드를 반환한다.
		inline PokerCard * GetCard(enum PLAYER player,
					   enum CARD_INDEX card_index){
			if(player >= player_list.size())
				return NULL;
			return player_list[player].GetCard(card_index);
		}

		//is_open 플래그가 지정된 카드를 반환한다.
		inline PokerCard * GetOpenCard(enum PLAYER player){
			return player_list[player].GetOpenCard();
		}

		//특정 플레이어의 카드에 is_open 플래그 지정
		inline void SetOpenCard(enum PLAYER player_num, 
					enum CARD_INDEX card_index){
			player_list[player_num].SetOpenCard(card_index);
		}

		//Setter
		inline bool SetUser(enum ONEPOKER::PLAYER player_num, PokerUser & player){
			if(player_list.size() == OnePokerDefault::MAX_USER)
				return false;
#ifdef ONEPOKER_DEBUG
			cout << "OnePoker SetUser" << endl;
#endif
			player_list.push_back(player);
			return true;
		}
		//Getter (판돈?)
		inline int GetStageMoney(){ return stage_money; }
	private:
		CardList * card_list;
		vector<PokerUser> player_list;
		int stage_money;
		vector<int> player_betting;
	};
};
#endif 
