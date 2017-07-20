#include "db/BlackList.hpp"
#include "util/Time.hpp"
using namespace std;
using namespace ONEPOKER;

BlackIP * BlackIP::instance = NULL;
BlackUser * BlackUser::instance = NULL;

bool BlackList::Search(string info){
	if(DataBase::QueryRun(SearchQuery(info))){
		if(DataBase::GetResult()){
			if(DataBase::GetRow()){
				DataBase::FreeData();
				return true;
			}
		}
	}		
	return false;
}

bool BlackList::Insert(string info, string reason){
	if(DataBase::QueryRun(InsertQuery(info, reason)))
		return true;
	return false;
}

bool BlackList::Remove(string info){
	if(DataBase::QueryRun(RemoveQuery(info)))
		return true;
	return false;
}

string & BlackIP::SearchQuery(string & info){
	query = "SELECT * FROM OP_BLACK_IP_TB WHERE ip = '" + info + "'";
#ifdef ONEPOKER_DEBUG
	cout << "BlackIP search query : " << query << endl;
#endif
	return query;
}

string & BlackIP::InsertQuery(string & info, string & reason){
	query = "INSERT INTO OP_BLACK_IP_TB VALUES(";
	query += "\"" + info + "\"";
	query += ",\"" + GetTimeyyyymmdd() + "\"";
	query += ",\"" + reason + "\")";
#ifdef ONEPOKER_DEBUG
	cout << "BlackIP insert query : " << query << endl;
#endif
	return query;
}

string & BlackIP::RemoveQuery(string & info){
	query = "DELETE FROM OP_BLACK_IP_TB WHERE ip = \"" + info + "\"";
#ifdef ONEPOKER_DEBUG
	cout << "BlackIP remove query : " << query << endl;
#endif
	return query;
}

string & BlackUser::SearchQuery(string & info){
	query = "SELECT user_num FROM OP_BLACK_USER_TB WHERE user_num = ";
	query+= "(SELECT user_num FROM OP_USER_TB WHERE id = '" + info + "')";
#ifdef ONEPOKER_DEBUG
	cout << "BlackUser search query : " << query << endl;
#endif
	return query;
}
string & BlackUser::InsertQuery(string & info, string & reason){
	query = "INSERT INTO OP_BLACK_USER_TB VALUES(";
	query+= "(SELECT user_num FROM OP_USER_TB WHERE id = '" + info +"')";
	query+= ",'" + GetTimeyyyymmdd() + "'";
	query+= ",'" + reason + "')";
#ifdef ONEPOKER_DEBUG
	cout << "BlackUser insert query : " << query << endl;
#endif
	return query;
}

string & BlackUser::RemoveQuery(string & info){
	query = "DELETE FROM OP_BLACK_USER_TB WHERE user_num = (SELECT user_num FROM OP_USER_TB WHERE id = '" + info + "')";
#ifdef ONEPOKER_DEBUG
	cout << "BlackUser remove query : " << info << endl;
#endif
	return query;
}
