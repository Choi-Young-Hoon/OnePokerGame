#ifndef __ONEPOKER_GAME_POKERCARD_HEADER__
#define __ONEPOKER_GAME_POKERCARD_HEADER__
#include "util/GameType.hpp"

namespace CARDGAME{
	class PokerCard{
	public:
		PokerCard(): is_open(false) {
			type = CARD_TYPE::CARD_NON_TYPE;
			win_card = name = CARD::CARD_NON;
		}
		~PokerCard(){}
		
		//카드 정보 입력
		inline void SetCard(int type
				, enum CARD name
				, enum CARD win){
			this->type = type;
			this->name = name;
			this->win_card = win;
		}
	
		//Setter
		inline void SetOpenCard(){ is_open = true; }
		inline void SetCloseCard(){ is_open = false; }
		//Getter
		inline int GetType(){ return type; }
		inline enum CARD GetName(){ return name; }
		inline enum CARD GetWinCard(){ return win_card; }
		inline bool IsOpen(){ return is_open; }
	private:
		int type;	//Up, Down or Shape flag
		enum CARD name;	//카드 종류
		enum CARD win_card;	//이길 수 있는 카드
		bool is_open;	//open 된 카드인지.
	};
};

#endif
