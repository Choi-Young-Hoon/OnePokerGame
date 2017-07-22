#ifndef __ONEPOKER_UTIL_GAMETYPE_HEADER__
#define __ONEPOKER_UTIL_GAMETYPE_HEADER__

#include <map>
#include <string>
using namespace std;

namespace ONEPOKER{
	//Player
	enum PLAYER{
		PLAYER_1 = 0,
		PLAYER_2,

		PLAYER_NON
	};

	//Game 결과
	enum GAME{
		LOSE = 0,
		WIN,
		DRAW
	};
	
	//카드의 문자열 저장
	static map<string, int> card_data;
	//card 의 데이터를 정수형으로 반환
	extern "C" int GetCardData(string data);
	//Map 데이터를 초기화
	extern "C" void CardDataMapInit();

	enum CARD{
/*NO CARD*/	CARD_NON = 0,
/*DOWN CARD*/	CARD_2 = 2, CARD_3, CARD_4, CARD_5, CARD_6, CARD_7,
/*UP CARD*/	CARD_8, CARD_9, CARD_10, CARD_K, CARD_Q, CARD_J, CARD_A
	}; 
	//카드 UP, DOWN 플래그
	enum CARD_TYPE{
		CARD_NON_TYPE = 0,
		CARD_DOWN, 
		CARD_UP
	};
	//두장의 카드중 인덱스
	enum CARD_INDEX{
		CARD_FIRST = 0,
		CARD_SECOND,
		CARD_NON_SELECT
	};
	
};
#endif
