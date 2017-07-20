#ifndef __ONEPOKER_GAME_POKERCARD_HEADER__
#define __ONEPOKER_GAME_POKERCARD_HEADER__
#include "game/OnePokerDefault.hpp"
#include "util/GameType.hpp"
namespace ONEPOKER{
	class PokerCard{
	public:
		PokerCard():is_open(false) {
			type = ONEPOKER::CARD_TYPE::CARD_NON_TYPE;
			win_card = name = ONEPOKER::CARD::CARD_NON;
		}
		~PokerCard(){}

		inline void SetCard(enum ONEPOKER::CARD_TYPE type
				, enum ONEPOKER::CARD name
				, enum ONEPOKER::CARD win){
			this->type = type;
			this->name = name;
			this->win_card = win;
		}
		
		enum ONEPOKER::GAME CheckWin(const PokerCard & card);

		inline void SetOpenCard(){ is_open = true; }
		inline void SetCloseCard(){ is_open = false; }
		inline enum ONEPOKER::CARD_TYPE GetType(){ return type; }
		inline enum ONEPOKER::CARD GetName(){ return name; }
		inline enum ONEPOKER::CARD GetWinCard(){ return win_card; }
		inline bool IsOpen(){ return is_open; }
	private:
		enum ONEPOKER::CARD_TYPE type;	//Up, Down flag
		enum ONEPOKER::CARD name;	//카드 종류
		enum ONEPOKER::CARD win_card;	//이길 수 있는 카드
		bool is_open;	//open 된 카드인지.
	};
};
#endif
