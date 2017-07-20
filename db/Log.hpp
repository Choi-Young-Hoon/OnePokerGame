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

		bool get_data(vector<string> * data){
			return DataBase::db_get_data(data, 
					DataBase::db_get_field_count());
		}

		bool get_log(string user){
			if(DataBase::db_query_run(getQuery(user)))
				if(DataBase::db_get_result())
					return true;
			return false;
		}

		bool write_log(ARGS ... arg){
			if(DataBase::db_query_run(writeQuery(arg...)))
				return true;
			return false;
		}
		
		virtual string & getQuery(string & user) = 0;
		virtual string & writeQuery(ARGS ... arg) = 0;
	};

	class MatchLog : public Log<string&, string&, enum ONEPOKER::PLAYER> {
	public:
		MatchLog():Log<string&, string&, enum ONEPOKER::PLAYER>(){}
		virtual ~MatchLog(){}

		virtual string & getQuery(string & user);
		virtual string & writeQuery(string & user1, string & user2
				, enum ONEPOKER::PLAYER winner);
	private:
		string query;
	};

	class AccessLog : public Log<string&, string&> {
	public:
		AccessLog():Log<string&, string&>(){}
		virtual ~AccessLog(){}
		virtual string & getQuery(string & user);
		virtual string & writeQuery(string & user, string & ip);
	private:
		string query;
	};
};
#endif
