#include "db/DataBase.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace ONEPOKER;

MYSQL DataBase::db;

enum ONEPOKER::OP_ERROR_FLAG DataBase::Connect(string ip, string user, string pwd){
	
	mysql_init(&db);

	if(!mysql_real_connect(&db, ip.c_str(), user.c_str(), pwd.c_str(),
				"ONEPOKER", 3306, (char*)NULL, 0))
		return OP_ERROR_FLAG::DB_CONNECT_ERROR;
	return OP_ERROR_FLAG::DB_CONNECT_SUCCESS;
}

void DataBase::Close(){
	mysql_close(&db);
}

bool DataBase::QueryRun(string & query){
#ifdef ONEPOKER_DEBUG
	cout << "DataBase db_query_run() : " << query << endl;
#endif
	if(mysql_query(&db, query.c_str()))
		return false;
	return true;
}

bool DataBase::GetResult(){
	db_result = mysql_store_result(&db);
	if(!db_result){ //반환 결과가 없으면
		mysql_free_result(db_result);
		return false;
	}
	return true;
}

bool DataBase::GetData(vector<string> * data, int field_count){
	(*data).clear();
	db_data = mysql_fetch_row(db_result);
	if(!db_data){
		mysql_free_result(db_result);
		return false;
	}
	
	for(int i = 0; i < field_count; i++)
		(*data).push_back(db_data[i]);
	return true;
}
