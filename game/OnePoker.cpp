#include "game/OnePoker.hpp"
#include "util/GameType.hpp"
#include "db/User.hpp"

using namespace std;
using namespace CARDGAME;
using namespace CARDGAME::ONEPOKER;

static enum PLAYER CheckWin(PokerCard & card1, PokerCard & card2){
	enum PLAYER result;
	if(card1.GetType() == card2.GetType()){ //UP UP, DOWN DOWN
		if(card1.GetName() > card2.GetName())
			result = PLAYER::PLAYER_1;
		else if(card1.GetName() < card2.GetName())
			result = PLAYER::PLAYER_2;
		else
			result = PLAYER::PLAYER_NON;
	} else if(card1.GetType() > card2.GetType()){ //UP DOWN
		if( (card1.GetName() == CARD::CARD_A) &&
		    (card2.GetName() == CARD::CARD_2) )
			result = PLAYER::PLAYER_2;
		else
			result = PLAYER::PLAYER_1;
	} else { //DOWN UP
		if( (card1.GetName() == CARD::CARD_2) &&
		    (card2.GetName() == CARD::CARD_A) )
			result = PLAYER::PLAYER_1;
		else
			result = PLAYER::PLAYER_2;
	}
	return result;
}
enum PLAYER OnePoker::CheckWinner() {
	vector<PokerCard> player1_card = player_list[PLAYER::PLAYER_1].GetOpenCard();
	vector<PokerCard> player2_card = player_list[PLAYER::PLAYER_2].GetOpenCard();

	//Open 카드 확인.
	if( (player1_card.size() != RULE::MAX_OPEN_CARD) &&
	    (player2_card.size() != RULE::MAX_OPEN_CARD))
		return PLAYER::PLAYER_NON;

	return CheckWin(player1_card[0], player2_card[0]);
}
