#include "db/DataBase.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace ONEPOKER;

MYSQL DataBase::db;

enum ONEPOKER::OP_ERROR_FLAG DataBase::db_connect(string ip, string user, string pwd){
	
	mysql_init(&db);

	if(!mysql_real_connect(&db, ip.c_str(), user.c_str(), pwd.c_str(),
				"ONEPOKER", 3306, (char*)NULL, 0))
		return OP_ERROR_FLAG::DB_CONNECT_ERROR;
	return OP_ERROR_FLAG::DB_CONNECT_SUCCESS;
}

void DataBase::db_close(){
	mysql_close(&db);
}

bool DataBase::db_query_run(string & query){
#ifdef ONEPOKER_DEBUG
	cout << "DataBase db_query_run() : " << query << endl;
#endif
	if(mysql_query(&db, query.c_str()))
		return false;
	return true;
}

bool DataBase::db_get_result(){
	dbResult = mysql_store_result(&db);
	if(!dbResult){ //반환 결과가 없으면
		mysql_free_result(dbResult);
		return false;
	}
	return true;
}

bool DataBase::db_get_data(vector<string> * data, int fieldCount){
	(*data).clear();
	dbData = mysql_fetch_row(dbResult);
	if(!dbData){
		mysql_free_result(dbResult);
		return false;
	}
	
	for(int i = 0; i < fieldCount; i++)
		(*data).push_back(dbData[i]);
	return true;
}
