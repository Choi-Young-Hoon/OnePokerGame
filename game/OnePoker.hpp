#ifndef __ONEPOKER_GAME_ONEPOKER__HEADER__
#define __ONEPOKER_GAME_ONEPOKER__HEADER__
#include "game/PokerUser.hpp"
#include "game/OnePokerDefault.hpp"
#include "util/GameType.hpp"
#include <iostream>
#include <vector>
using namespace std;

namespace ONEPOKER{
	class OnePoker : public OnePokerDefault{
	public:
		OnePoker():stage_money(0){}
		OnePoker(PokerUser * player1, PokerUser * player2)
			:stage_money(0){
			player_list[ONEPOKER::PLAYER::PLAYER_1] = player1;
			player_list[ONEPOKER::PLAYER::PLAYER_2] = player2;
		}

		enum ONEPOKER::PLAYER CheckWinner();
		bool GetRandomCard();
		bool Betting(enum PLAYER player, int betting_money);
		void GameFinish();

		inline PokerUser * GetUser(enum PLAYER player){
			if((player >= OnePokerDefault::MAX_USER) && 
			   (player >= player_list.size()))
				return PLAYER::PLAYER_NON;
			return player_list[player];
		}
		inline PokerCard * GetCard(enum PLAYER player,
					   enum CARD_INDEX card_index){
			if(player >= player_list.size())
				return NULL;
			return player_list[player]->GetCard(card_index);
		}
		inline bool SetOpenCard(enum PLAYER player_num, 
					enum CARD_INDEX card_index){

		}
		inline bool setUser(enum ONEPOKER::PLAYER player_num, PokerUser * player){
			if(player_list[player_num] != NULL)
				return false;
			player_list[player_num] = player;
			return true;
		}
		inline int GetStageMoney(){ return stage_money; }
	private:
		vector<PokerUser *> player_list(NULL, OnePokerDefault::MAX_USER);
		int stage_money;
		vector<int> player_betting(0, OnePokerDefault::MAX_USER);
	};
};
#endif 
