#ifndef __ONEPOKER_UTIL_GAMETYPE_HEADER__
#define __ONEPOKER_UTIL_GAMETYPE_HEADER__
#include <map>
#include <string>
using namespace std;

namespace ONEPOKER{
	enum PLAYER{
		PLAYER_1 = 0,
		PLAYER_2,

		PLAYER_NON
	};

	enum GAME{
		LOSE = 0,
		WIN,
		DRAW
	};
	
	static map<string, int> card_data;
	extern "C" int GetCardData(string data);
	extern "C" void CardDataMapInit();

	enum CARD{
/*NO CARD*/	CARD_NON = 0,
/*DOWN CARD*/	CARD_2 = 2, CARD_3, CARD_4, CARD_5, CARD_6, CARD_7,
/*UP CARD*/	CARD_8, CARD_9, CARD_10, CARD_K, CARD_Q, CARD_J, CARD_A
	}; 

	enum CARD_TYPE{
		CARD_NON_TYPE = 0,
		CARD_DOWN, 
		CARD_UP
	};

	enum CARD_INDEX{
		CARD_FIRST = 0,
		CARD_SECOND,
		CARD_NON_SELECT
	};
	
};
#endif
