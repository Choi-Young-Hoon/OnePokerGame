#ifndef __ONEPOKER_DB_USER_HEADER__
#define __ONEPOKER_DB_USER_HEADER__
#include "db/DataBase.hpp"
#include <iostream>
#include <string>
using namespace std;

namespace CARDGAME{
	class User;
	class UserData{
	public:
		UserData(){}
		~UserData(){}

		// Setter ///////////////////////////////////////////
		inline void SetData(string pwd, string email){
			user_pwd = pwd;
			user_email = email;
		}
		inline void SetStat(int money, bool win){
			user_money += money;
			(win) ? user_win++ : user_lose++;
		}
		inline void SetMoney(int money){
			user_money += money;
		}
		inline void SetRecentDate(string date){
			user_recent_access_date = date;
		}

		// Getter //////////////////////////////////////////
		inline int GetNum(){ return user_num; }
		inline string & GetId(){ return user_id; }
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
		
		/*
		 * 유저 추가
		 * @param
		 * id - 계정
		 * pwd - 비밀번호
		 * email - 유저 email
		 * @return
		 * 성공시 - true
		 * 실패시 - false
		 */
		bool Insert(string id, string pwd, string email);
		
		/*
		 * 유저 제거
		 * @param
		 * user_info - 제거할 정보가 유저의 정보가 들어있는 UserData 객체
		 * @return
		 * 성공시 - true
		 * 실패시 - false
		 */
		bool Remove(UserData & user_info);

		/*
		 * Search 함수 내부에서 호출한다.
		 * UserData 객체에 data를 입력한다.
		 * @param
		 * user_info - 데이터를 저장할 UserData 객체
		 * data - 유저 검색에 대한 쿼리 결과를 갖고있는vector
		 */
		void SetData(UserData * user_info, vector<string> & data);

		/*
		 * 유저를 검색하고 데이터를 받아온다.
		 * @param
		 * id - 검색할 유저 계정
		 * pwd - 검색할 유저 비밀번호
		 * user_info - 검색한 유저의 정보를 저장할 UserData 객체
		 * @return
		 * 유저에 대한 검색결과가 있을경우 - true
		 * 없을경우 - false
		 */
		bool Search(string id, string pwd, UserData * user_info);
		
		/*
		 * 유저의 정보를 갱신한다.
		 * @param
		 * user_info - 업데이트할 유저 정보가 담긴 UserData 객체
		 * @return
		 * 성공시 - true
		 * 실패시 - false
		 */
		bool Update(UserData * user_info);

	private:
		string query;
		vector<string> data;
	};
};	
#endif
