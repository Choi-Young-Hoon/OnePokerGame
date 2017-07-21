#ifndef __ONPOKER_DB_GAMESETTING_HEADER__
#define __ONPOKER_DB_GAMESETTING_HEADER__
#include "db/DataBase.hpp"
#include "game/PokerCard.hpp"
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>
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
		static inline Rating * GetInstance(){
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
		
		/*
		 * DB의 데이터가 각 ROW 마다 해당 함수로 넘어온다.
		 * @param
		 * data - db 쿼리 결과의 ROW 데이터
		 * @return
		 * 데이터 추가 성공시 - true
		 * 실패시 - false
		 */
		virtual bool InsertData(vector<string> & data);
		
		/*
		 * money 값에 대한 Rating 값을 구한다.
		 * @param
		 * money - Rating 값을 구할 money 값
		 * @return
		 * money에 대한 Rating 값을 반환한다.
		 */
		int FindRating(int money);
	private:
		Rating(){}
		static Rating * instance;
		map<int, int> rating_list;
		string query;
	};

	class CardList : public GameSetting {
	public:
		static inline CardList * GetInstance(){
			if(instance == NULL){
				srand(time(NULL));
				instance = new CardList();
			}
			return instance;
		}
		
		/*
		 * Rating 정보를 가져오기 위한 쿼리를 반환한다.
		 * @return
		 * 쿼리 반환
		 */
		virtual string & GetQuery();
		
		/*
		 * DB의 데이터가 각 ROW 마다 해당 함수로 넘어온다.
		 * @param
		 * data - db 쿼리 결과의 ROW 데이터
		 * @return
		 * 데이터 추가 성공시 - true
		 * 실패시 - false
		 */
		virtual bool InsertData(vector<string> & data);
		
		/*
		 * card_list 를 참고 하여
		 * 저장되어 있는 카드중 랜덤하게 반환한다.
		 */
		PokerCard GetRandomCard();
	private:
		CardList(){}
		static CardList * instance;
		vector<PokerCard> card_list;
		string query;
	};
};
#endif
