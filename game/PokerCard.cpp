#include "game/PokerCard.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace ONEPOKER;

enum ONEPOKER::GAME PokerCard::check_win(const PokerCard & card){
	enum ONEPOKER::GAME result;
	if(type == card.type){ //UP UP, DOWN DOWN
		if(name > card.name)
			result = GAME::WIN;
		else if(name < card.name)
			result = GAME::LOSE;
		else
			result = GAME::DRAW;
	} else if(this->type > card.type){ // UP DOWN
		if( (card.name == CARD::CARD_2) &&
		    (this->name == CARD::CARD_A) )
			result = GAME::LOSE;
		else
			result = GAME::WIN;
	} else { // DOWN UP
		if( (this->name == CARD::CARD_2) && 
		    (card.name == CARD::CARD_A) )
			result = GAME::WIN;
		else
			result = GAME::LOSE;
	}
	return result;
}
