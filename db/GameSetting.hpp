#ifndef __ONPOKER_DB_GAMESETTING_HEADER__
#define __ONPOKER_DB_GAMESETTING_HEADER__
#include "db/DataBase.hpp"
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
		bool get_data();

		virtual string & getQuery() = 0;
	};

	class Rating : public GameSetting {
	public:
		inline Rating * getInstance(){
			if(!instance)
				instance = new Rating();
			return instance;
		}

		/*
		 * Rating 정보를 가져오기 위한 쿼리를 반환한다.
		 * @return
		 * 쿼리 반환
		 */
		virtual string & getQuery();
		int find_rating(int money);
	private:
		Rating(){}
		Rating * instance;
		string query;
	};
};
#endif
