#ifndef __ONEPOKER_GAME_ONEPOKERDEFAULT_HEADER__
#define __ONEPOKER_GAME_ONEPOKERDEFAULT_HEADER__
namespace ONEPOKER{
	class OnePokerDefault{
	public:
		OnePokerDefault(){}
		~OnePokerDefault(){}
		
		static const int MAX_USER = 2; //최대 접속 가능 유저.
		static const int MAX_VIEW = 0; //관전 가능 수
		static const int MAX_CARD = 2; //한 유저가 최대 가질수 있는 카드 수
	};
};
#endif
