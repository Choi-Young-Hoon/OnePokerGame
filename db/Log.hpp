#ifndef __ONEPOKER_DB_LOG_HEADER__
#define __ONEPOKER_DB_LOG_HEADER__
#include "db/DataBase.hpp"
#include "util/GameType.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace ONEPOKER{
	template <typename ... ARGS>
	class Log : public DataBase {
	public:
		Log(){}
		virtual ~Log(){}

		/*
		 * GetLog 결과가 성공했을 경우 데이터를 받는다.
		 * @param
		 * data - 반환받을 vector 쿼리결과의 필드 순서대로 삽입된다.
		 * @return
		 * 반환할 결과가 있는경우 - true
		 * 반환할 결과가 없는겅우 - false
		 */
		inline bool GetData(vector<string> * data){
			return DataBase::GetData(data, 
					DataBase::GetFieldCount());
		}

		/*
		 * user의 기록을 검사한다.
		 * @param
		 * user - 검색할 계정
		 * @return
		 * 쿼리에 성공하고 결과가 있을 경우 - true
		 * 쿼리에 실패하거나 결과가 없을 경우 - false
		 */
		bool GetLog(string user){
			if(DataBase::QueryRun(GetQuery(user)) &&
			   DataBase::GetResult())
					return true;
			return false;
		}


		/*
		 * Log를 작성한다. 각 상속받는 class 별로 인자가 다르다.
		 * @return
		 * 쿼리 성공시 - true
		 * 쿼리 실패시 - false
		 */
		bool WriteLog(ARGS ... arg){
			if(DataBase::QueryRun(WriteQuery(arg...)))
				return true;
			return false;
		}
		
		virtual string & GetQuery(string & user) = 0;
		virtual string & WriteQuery(ARGS ... arg) = 0;
	};

	class MatchLog : public Log<string&, string&, enum ONEPOKER::PLAYER> {
	public:
		MatchLog():Log<string&, string&, enum ONEPOKER::PLAYER>(){}
		virtual ~MatchLog(){}

		/*
		 * user에 대한 Match log를 검색하기 위한 쿼리를 반환한다.
		 */
		virtual string & GetQuery(string & user);

		/*
		 * Match log 작성을 위한 쿼리를 반환한다.
		 * @param
		 * user1 - 유저 계정
		 * user2 - 유저 계정
		 * winner - 승리한 유저 값
		 */
		virtual string & WriteQuery(string & user1, string & user2
				, enum ONEPOKER::PLAYER winner);
	private:
		string query;
	};

	class AccessLog : public Log<string&, string&> {
	public:
		AccessLog():Log<string&, string&>(){}
		virtual ~AccessLog(){}

		/*
		 * user에 대한 Access log를 검색하기 위한 쿼리를 반환한다.
		 */
		virtual string & GetQuery(string & user);

		/*
		 * Access log 작성을 위한 쿼리를 반환한다.
		 * @param
		 * user - 유저 꼐정
		 * ip - 접속 ip
		 */
		virtual string & WriteQuery(string & user, string & ip);
	private:
		string query;
	};
};
#endif
