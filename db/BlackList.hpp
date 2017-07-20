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
		bool search(string info);
		bool insert(string info, string reason);
		bool remove(string info);

		virtual string & searchQuery(string & info) = 0;
		virtual string & insertQuery(string & info, string & reason) = 0;
		virtual string & removeQuery(string & info) = 0;
	};

	class BlackIP : public BlackList {
	public:
		virtual ~BlackIP(){
			if(instance)
				delete instance;
		}
		static inline BlackIP * getInstance(){
			if(!instance)
				instance = new BlackIP();
			return instance;
		}
		virtual string & searchQuery(string & info);
		virtual string & insertQuery(string & info, string & reason);
		virtual string & removeQuery(string & info);
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
		static inline BlackUser * getInstance(){
			if(!instance)
				instance = new BlackUser();
			return instance;
		}
		virtual string & searchQuery(string & info);
		virtual string & insertQuery(string & info, string & reason);
		virtual string & removeQuery(string & info);
	private:
		BlackUser(){}
		static BlackUser * instance;
		string query;
	};
};

#endif
