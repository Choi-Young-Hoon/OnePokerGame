#include "db/BlackList.hpp"
#include "util/Time.hpp"
using namespace std;
using namespace ONEPOKER;

BlackIP * BlackIP::instance = NULL;
BlackUser * BlackUser::instance = NULL;

bool BlackList::search(string info){
	if(DataBase::db_query_run(searchQuery(info))){
		if(DataBase::db_get_result()){
			if(DataBase::db_get_row()){
				DataBase::db_free_data();
				return true;
			}
		}
	}		
	return false;
}

bool BlackList::insert(string info, string reason){
	if(DataBase::db_query_run(insertQuery(info, reason)))
		return true;
	return false;
}

bool BlackList::remove(string info){
	if(DataBase::db_query_run(removeQuery(info)))
		return true;
	return false;
}

string & BlackIP::searchQuery(string & info){
	query = "SELECT * FROM OP_BLACK_IP_TB WHERE ip = '" + info + "'";
#ifdef ONEPOKER_DEBUG
	cout << "BlackIP search query : " << query << endl;
#endif
	return query;
}

string & BlackIP::insertQuery(string & info, string & reason){
	query = "INSERT INTO OP_BLACK_IP_TB VALUES(";
	query += "\"" + info + "\"";
	query += ",\"" + get_time_yyyymmdd() + "\"";
	query += ",\"" + reason + "\")";
#ifdef ONEPOKER_DEBUG
	cout << "BlackIP insert query : " << query << endl;
#endif
	return query;
}

string & BlackIP::removeQuery(string & info){
	query = "DELETE FROM OP_BLACK_IP_TB WHERE ip = \"" + info + "\"";
#ifdef ONEPOKER_DEBUG
	cout << "BlackIP remove query : " << query << endl;
#endif
	return query;
}

string & BlackUser::searchQuery(string & info){
	query = "SELECT user_num FROM OP_BLACK_USER_TB WHERE user_num = ";
	query+= "(SELECT user_num FROM OP_USER_TB WHERE id = '" + info + "')";
#ifdef ONEPOKER_DEBUG
	cout << "BlackUser search query : " << query << endl;
#endif
	return query;
}
string & BlackUser::insertQuery(string & info, string & reason){
	query = "INSERT INTO OP_BLACK_USER_TB VALUES(";
	query+= "(SELECT user_num FROM OP_USER_TB WHERE id = '" + info +"')";
	query+= ",'" + get_time_yyyymmdd() + "'";
	query+= ",'" + reason + "')";
#ifdef ONEPOKER_DEBUG
	cout << "BlackUser insert query : " << query << endl;
#endif
	return query;
}

string & BlackUser::removeQuery(string & info){
	query = "DELETE FROM OP_BLACK_USER_TB WHERE user_num = (SELECT user_num FROM OP_USER_TB WHERE id = '" + info + "')";
#ifdef ONEPOKER_DEBUG
	cout << "BlackUser remove query : " << info << endl;
#endif
	return query;
}
