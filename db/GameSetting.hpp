#ifndef __ONPOKER_DB_GAMESETTING_HEADER__
#define __ONPOKER_DB_GAMESETTING_HEADER__
#include "db/DataBase.hpp"
#include "game/PokerCard.hpp"
#include <iostream>
#include <string>
using namespace std;

namespace ONEPOKER{
	
	class GameSetting : public DataBase {
	public:
		GameSetting(){}
		~GameSetting(){}

		/*
		 * 데이터를 가져온다.
		 * @return
		 * 성공시 - true
		 * 실패시 - false
		 */
		bool GetData();

		virtual string & GetQuery() = 0;
		virtual bool InsertData(vector<string> & data) = 0;
	};

	class Rating : public GameSetting {
	public:
		inline Rating * GetInstance(){
			if(instance == NULL)
				instance = new Rating();
			return instance;
		}

		/*
		 * Rating 정보를 가져오기 위한 쿼리를 반환한다.
		 * @return
		 * 쿼리 반환
		 */
		virtual string & GetQuery();
		virtual bool InsertData(vector<string> & data);
		int FindRating(int money);
	private:
		Rating(){}
		Rating * instance;
		string query;
	};

	class CardList : public GameSetting {
	public:
		inline CardList * GetInstance(){
			if(instance == NULL)
				instance = new CardList();
			return instance;
		}
		
		virtual string & GetQuery();
		virtual bool InsertData(vector<string> & data);
		PokerCard GetRandomCard();
	private:
		CardList(){}
		CardList * instance;
		vector<PokerCard> card_list;
		string query;
	};
};
#endif
