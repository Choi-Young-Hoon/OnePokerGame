#ifndef __ONEPOKER_DB_USER_HEADER__
#define __ONEPOKER_DB_USER_HEADER__
#include "db/DataBase.hpp"
#include <iostream>
#include <string>
using namespace std;

namespace ONEPOKER{
	class User;
	class UserData{
	public:
		UserData(){}
		~UserData(){}

		//Setter
		inline void SetData(string pwd, string email){
			user_pwd = pwd;
			user_email = email;
		}
		inline void SetStat(int money, bool win){
			user_money += money;
			(win) ? user_win++ : user_lose++;
		}
		inline void SetRecentDate(string date){
			user_recent_access_date = date;
		}
		//Getter
		inline int GetNum(){ return user_num; }
		inline string & GetId(){ return user_email; }
		inline string & GetPwd(){ return user_pwd; }
		inline string & GetEmail(){ return user_email; }
		inline string & GetAccessDate(){ return user_recent_access_date; }
		inline bool IsCert(){ return user_email_cert; }
		inline int GetMoney(){ return user_money; }
		inline int GetWin(){ return user_win; }
		inline int GetLose(){ return user_lose; }

		friend class User;
	private:
		int user_num;
		string user_id;
		string user_pwd;
		string user_email;
		string user_recent_access_date;
		bool user_email_cert;
		int user_money;
		int user_win;
		int user_lose;
	};

	class User : public DataBase {
	public:
		User(){}
		~User(){}

		bool Insert(string id, string pwd, string email);
		bool Remove(UserData & user_info);
		void SetData(UserData * user_info, vector<string> & data);
		bool Search(string id, string pwd, UserData * user_info);
		bool Update(UserData * user_info);

		friend class UserData;
	private:
		string query;
		vector<string> data;
	
	};
};	
#endif
