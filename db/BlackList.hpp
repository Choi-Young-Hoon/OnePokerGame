#ifndef __ONEPOKER_DB_BLACKLIST_HEADER__
#define __ONEPOKER_DB_BLACKLIST_HEADER__

#include "db/DataBase.hpp"
#include "util/Time.hpp"
#include <iostream>
#include <string>
using namespace std;

namespace ONEPOKER{
	class BlackList : public DataBase {
	public:
		BlackList(){}
		virtual ~BlackList(){}
		bool Search(string info);
		bool Insert(string info, string reason);
		bool Remove(string info);

		virtual string & SearchQuery(string & info) = 0;
		virtual string & InsertQuery(string & info, string & reason) = 0;
		virtual string & RemoveQuery(string & info) = 0;
	};

	class BlackIP : public BlackList {
	public:
		virtual ~BlackIP(){
			if(instance)
				delete instance;
		}
		static inline BlackIP * GetInstance(){
			if(!instance)
				instance = new BlackIP();
			return instance;
		}
		virtual string & SearchQuery(string & info);
		virtual string & InsertQuery(string & info, string & reason);
		virtual string & RemoveQuery(string & info);
	private:
		BlackIP(){}
		static BlackIP * instance;
		string query;
	};


	class BlackUser : public BlackList {
	public:
		virtual ~BlackUser(){
			if(instance)
				delete instance;
		}
		static inline BlackUser * GetInstance(){
			if(!instance)
				instance = new BlackUser();
			return instance;
		}
		virtual string & SearchQuery(string & info);
		virtual string & InsertQuery(string & info, string & reason);
		virtual string & RemoveQuery(string & info);
	private:
		BlackUser(){}
		static BlackUser * instance;
		string query;
	};
};

#endif
