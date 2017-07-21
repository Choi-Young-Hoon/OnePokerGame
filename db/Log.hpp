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

		bool GetData(vector<string> * data){
			return DataBase::GetData(data, 
					DataBase::GetFieldCount());
		}

		bool GetLog(string user){
			if(DataBase::QueryRun(GetQuery(user)) &&
			   DataBase::GetResult())
					return true;
			return false;
		}

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

		virtual string & GetQuery(string & user);
		virtual string & WriteQuery(string & user1, string & user2
				, enum ONEPOKER::PLAYER winner);
	private:
		string query;
	};

	class AccessLog : public Log<string&, string&> {
	public:
		AccessLog():Log<string&, string&>(){}
		virtual ~AccessLog(){}
		virtual string & GetQuery(string & user);
		virtual string & WriteQuery(string & user, string & ip);
	private:
		string query;
	};
};
#endif
