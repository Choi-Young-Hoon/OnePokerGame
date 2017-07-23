#ifndef __ONEPOKER_GAME_CARDGAME_HEADER__
#define __ONEPOKER_GAME_CARDGAME_HEADER__
#include "game/PokerUser.hpp"
#include "game/PokerCard.hpp"
#include "util/GameType.hpp"
using namespace CARDGAME;
#include <map>
using namespace std;

namespace CARDGAME {
	class CardGame {
	public:
		CardGame() : stage_money(0) {}
		virtual ~CardGame(){}

		inline void AddStageMoney(int money){ stage_money += money; }
		inline int GetStageMoney(){ return stage_money; }
		//랜덤하게 섞은 덱을 반환한다.	
		vector<PokerCard> GetRandomMixDec();

		//게임 종료
		virtual void GameFinish() = 0;
		//이긴 유저 반환.
		virtual enum PLAYER CheckWinner() = 0;
		
		//Getter
		//유저 반환	
		virtual PokerUser * GetUser(enum PLAYER) = 0;
		//카드 반환
		virtual PokerCard * GetCard(enum PLAYER, enum CARD_INDEX) = 0;
		//공개된 카드 반환.
		virtual vector<PokerCard> GetOpenCardList(enum PLAYER) = 0;
		//카드 개수 반환
		virtual inline int GetCardCount(enum PLAYER) = 0;
		//유저의 수 반환
		virtual inline int GetUserCount() = 0;
		
		//Setter
		//유저 추가
		virtual inline bool SetUser(PokerUser &) = 0;
		//유저에게 카드 추가
		virtual inline bool SetCard(enum PLAYER, PokerCard &) = 0;
		//open 카드 지정
		virtual bool SetOpenCard(enum PLAYER, int) = 0;
	private:
		int stage_money;
	};
};

#endif
