#ifndef __ONEPOKER_GAME_ONEPOKER__HEADER__
#define __ONEPOKER_GAME_ONEPOKER__HEADER__

#ifndef __ONEPOKER_DB_GAMESETTING_HEADER__
#include "db/GameSetting.hpp"
#endif

#include "game/CardGame.hpp"
#include "game/PokerUser.hpp"
#include "util/GameType.hpp"
#include "util/GameRule.hpp"
#include <iostream>
#include <vector>
using namespace std;


namespace CARDGAME{
namespace ONEPOKER{
	class OnePoker : public CardGame{
	public:
		OnePoker(){}
		OnePoker(PokerUser player1, PokerUser player2){
				player_list.push_back(player1);	
				player_list.push_back(player2);
		}
		
		virtual ~OnePoker(){}

		//이긴 유저 번호를 번환
		virtual enum PLAYER CheckWinner();

		//게임이 끝나 종료 작업
		virtual void GameFinish(){
			for(unsigned int i = 0; i < player_list.size(); i++){
				player_list[i].CardClear();
				if(winner == i)
					player_list[i].GetUserData()->SetStat(player_betting[i], true);
				else
					player_list[i].GetUserData()->SetStat(player_betting[i] * (-1), false);
					
			}
		}
		
		//특정 유저의 판돈 배팅
		inline void Betting(enum PLAYER player, int betting_money){
			player_betting[player] += betting_money;
			CardGame::AddStageMoney(betting_money);
		}

		//특정 유저의 PokerUser 객체를 반환한다.
		virtual PokerUser * GetUser(enum PLAYER player){
			if(((int)player >= (int)RULE::MAX_USER) && 
			   (player >= player_list.size()))
				return NULL;
			return &player_list[player];
		}

		//카드 개수 반환	
		virtual inline int GetUserCount(){
			return player_list.size();
		}

		//특정 유저의 카드를 반환한다.
		virtual PokerCard * GetCard(enum PLAYER player,
					   enum CARD_INDEX card_index){
			if((int)player >= player_list.size())
				return NULL;
			return player_list[player].GetCard(card_index);
		}

		virtual inline int GetCardCount(enum PLAYER player){
			return player_list[player].GetCardCount();
		}


		//is_open 플래그가 지정된 카드를 반환한다.
		virtual vector<PokerCard> GetOpenCardList(enum PLAYER player){
			return player_list[player].GetOpenCard();
		}

		//특정 플레이어의 카드에 is_open 플래그 지정
		virtual bool SetOpenCard(enum PLAYER player_num, 
					int card_index){
			if(player_list[player_num].GetCardCount() <= card_index)
				return false;
			player_list[player_num].SetOpenCard(card_index);
			return true;
		}

		//Setter

		virtual inline bool SetCard(enum PLAYER player_num, PokerCard & card){
			if(player_list[player_num].GetCardCount() >= RULE::MAX_CARD)
				return false;
			player_list[player_num].AddCard(card);
			return true;
		}
		virtual inline bool SetUser(PokerUser & player){
			if(player_list.size() == RULE::MAX_USER)
				return false;
#ifdef ONEPOKER_DEBUG
			cout << "OnePoker SetUser" << endl;
#endif
			player_list.push_back(player);
			player_betting.push_back(0);
			return true;
		}
	private:
		vector<PokerCard> card_dec;
		vector<PokerUser> player_list;
		vector<int> player_betting;
		enum PLAYER winner;
	};
};
};
#endif 
