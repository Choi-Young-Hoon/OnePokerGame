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
		inline void SetCard(enum CARD_TYPE type
				, enum CARD name
				, enum CARD win){
			this->type = type;
			this->name = name;
			this->win_card = win;
		}
	
		/*
		//현재 카드가 card 를 이기는지 확인.
		enum GAME CheckWin(const PokerCard & card);
		*/
		
		//Setter
		inline void SetOpenCard(){ is_open = true; }
		inline void SetCloseCard(){ is_open = false; }
		//Getter
		inline enum CARD_TYPE GetType(){ return type; }
		inline enum CARD GetName(){ return name; }
		inline enum CARD GetWinCard(){ return win_card; }
		inline bool IsOpen(){ return is_open; }
	private:
		enum CARD_TYPE type;	//Up, Down flag
		enum CARD name;	//카드 종류
		enum CARD win_card;	//이길 수 있는 카드
		bool is_open;	//open 된 카드인지.
	};
};

#endif
