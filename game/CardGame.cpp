#include "game/CardGame.hpp"
#include "game/OnePoker.hpp"

using namespace CARDGAME;

extern "C" CardGame * SelectGameMode(enum GAME_MODE mode){
	switch(mode){
		case GAME_ONEPOKER:
			return new ONEPOKER::OnePoker();
	}
	return NULL;
}
