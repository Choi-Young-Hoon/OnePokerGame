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
		inline void setData(string pwd, string email){
			userPwd = pwd;
			userEmail = email;
		}
		inline void setStat(int money, bool win){
			userMoney += money;
			(win) ? userWin++ : userLose++;
		}
		inline void setRecentDate(string date){
			userRecentAccessDate = date;
		}
		//Getter
		inline int getNum(){ return userNum; }
		inline string & getId(){ return userEmail; }
		inline string & getPwd(){ return userPwd; }
		inline string & getEmail(){ return userEmail; }
		inline string & getAccessDate(){ return userRecentAccessDate; }
		inline bool IsCert(){ return userEmailCert; }
		inline int getMoney(){ return userMoney; }
		inline int getWin(){ return userWin; }
		inline int getLose(){ return userLose; }

		friend class User;
	private:
		int userNum;
		string userId;
		string userPwd;
		string userEmail;
		string userRecentAccessDate;
		bool userEmailCert;
		int userMoney;
		int userWin;
		int userLose;
	};

	class User : public DataBase {
	public:
		User(){}
		~User(){}

		bool insert(string id, string pwd, string email);
		bool remove(UserData & userInfo);
		void set_data(UserData * userInfo, vector<string> & data);
		bool search(string id, string pwd, UserData * userInfo);
		bool update(UserData * userInfo);

		friend class UserData;
	private:
		string query;
		vector<string> data;
	
	};
};	
#endif
