#include "db/User.hpp"
#include "util/DataBaseType.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
using namespace ONEPOKER;

bool User::insert(string id, string pwd, string email){
	query = "INSERT INTO OP_USER_TB(id, pass, email, rating_code) ";
	query+= "VALUES('" + id + "', '" + pwd + "', '" + email + "', 1)";
#ifdef ONEPOKER_DEBUG
	cout << "User insert query : " << query << endl;
#endif
	if(DataBase::db_query_run(query))
		return true;
	return false;
}

bool User::remove(UserData & userInfo){
	query = "DELETE FROM OP_USER_TB WHERE user_num = " + to_string(userInfo.getNum());
#ifdef ONEPOKER_DEBUG
	cout << "User delete query : " << query << endl;
#endif
	if(DataBase::db_query_run(query))
		return true;
	return false;
}

void User::set_data(UserData * userInfo, vector<string> & data){

#ifdef ONEPOKER_DEBUG
	cout << "User set_data() data.size() : " << data.size() << endl;
#endif

	userInfo->userNum = atoi(data[USER_TB::USER_NUM].c_str());
	userInfo->userId = data[USER_TB::USER_ID];
	userInfo->userPwd = data[USER_TB::USER_PWD];
	userInfo->userEmail = data[USER_TB::USER_EMAIL];
	if(data[USER_EMAIL_CERT] == DB_DATA_ENUM[DB_DATA_TYPE::EMAIL_CERT_YES])
		userInfo->userEmailCert = true;
	else 
		userInfo->userEmailCert = false;
	userInfo->userMoney = atoi(data[USER_TB::USER_MONEY].c_str());
	userInfo->userWin = atoi(data[USER_TB::USER_WIN].c_str());
	userInfo->userLose = atoi(data[USER_TB::USER_LOSE].c_str());
}

bool User::search(string id, string pwd, UserData * userInfo){
	query = "SELECT * FROM OP_USER_TB WHERE ";
	query+= "id = '" + id + "' ";
	query+= "AND pass = '" + pwd + "'";
#ifdef ONEPOKER_DEBUG
	cout << "User select query : " << query << endl;
#endif
	if(DataBase::db_query_run(query)){
		if(DataBase::db_get_result()) {
			if(DataBase::db_get_data(&data, DataBase::db_get_field_count())){
				if(userInfo != NULL)
					set_data(userInfo, data);
				DataBase::db_free_data();
				return true;
			}
			else
				return false;
		}
	}
	return false;
}

bool User::update(UserData * userInfo){
	query = "UPDATE OP_USER_TB SET ";
	query+= "pass = '" + userInfo->getPwd() + "' ";
	query+= ", email_cert = ";
	query+= (userInfo->IsCert()) ? "'O'" : "'X'";
	query+= ", resent_access_date = '" + userInfo->getAccessDate() + "'";
	query+= ", money = " + to_string(userInfo->getMoney());
	query+= ", win = " + to_string(userInfo->getWin());
	query+= ", lose = " + to_string(userInfo->getLose());
	query+= " WHERE user_num = " + to_string(userInfo->getNum());
#ifdef ONEPOKER_DEBUG
	cout << "User update query : " << query << endl;
#endif
	if(DataBase::db_query_run(query))
		return true;
	return false;
}
