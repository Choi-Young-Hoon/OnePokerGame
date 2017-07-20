#include "db/User.hpp"
#include "util/DataBaseType.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
using namespace ONEPOKER;

bool User::Insert(string id, string pwd, string email){
	query = "INSERT INTO OP_USER_TB(id, pass, email, rating_code) ";
	query+= "VALUES('" + id + "', '" + pwd + "', '" + email + "', 1)";
#ifdef ONEPOKER_DEBUG
	cout << "User insert query : " << query << endl;
#endif
	if(DataBase::QueryRun(query))
		return true;
	return false;
}

bool User::Remove(UserData & user_info){
	query = "DELETE FROM OP_USER_TB WHERE user_num = " + to_string(user_info.GetNum());
#ifdef ONEPOKER_DEBUG
	cout << "User delete query : " << query << endl;
#endif
	if(DataBase::QueryRun(query))
		return true;
	return false;
}

void User::SetData(UserData * user_info, vector<string> & data){

#ifdef ONEPOKER_DEBUG
	cout << "User set_data() data.size() : " << data.size() << endl;
#endif

	user_info->user_num = atoi(data[USER_TB::USER_NUM].c_str());
	user_info->user_id = data[USER_TB::USER_ID];
	user_info->user_pwd = data[USER_TB::USER_PWD];
	user_info->user_email = data[USER_TB::USER_EMAIL];
	if(data[USER_EMAIL_CERT] == DB_DATA_ENUM[DB_DATA_TYPE::EMAIL_CERT_YES])
		user_info->user_email_cert = true;
	else 
		user_info->user_email_cert = false;
	user_info->user_money = atoi(data[USER_TB::USER_MONEY].c_str());
	user_info->user_win = atoi(data[USER_TB::USER_WIN].c_str());
	user_info->user_lose = atoi(data[USER_TB::USER_LOSE].c_str());
}

bool User::Search(string id, string pwd, UserData * user_info){
	query = "SELECT * FROM OP_USER_TB WHERE ";
	query+= "id = '" + id + "' ";
	query+= "AND pass = '" + pwd + "'";
#ifdef ONEPOKER_DEBUG
	cout << "User select query : " << query << endl;
#endif
	if(DataBase::QueryRun(query)){
		if(DataBase::GetResult()) {
			if(DataBase::GetData(&data, DataBase::GetFieldCount())){
				if(user_info != NULL)
					SetData(user_info, data);
				DataBase::FreeData();
				return true;
			}
			else
				return false;
		}
	}
	return false;
}

bool User::Update(UserData * user_info){
	query = "UPDATE OP_USER_TB SET ";
	query+= "pass = '" + user_info->GetPwd() + "' ";
	query+= ", email_cert = ";
	query+= (user_info->IsCert()) ? "'O'" : "'X'";
	query+= ", resent_access_date = '" + user_info->GetAccessDate() + "'";
	query+= ", money = " + to_string(user_info->GetMoney());
	query+= ", win = " + to_string(user_info->GetWin());
	query+= ", lose = " + to_string(user_info->GetLose());
	query+= " WHERE user_num = " + to_string(user_info->GetNum());
#ifdef ONEPOKER_DEBUG
	cout << "User update query : " << query << endl;
#endif
	if(DataBase::QueryRun(query))
		return true;
	return false;
}
