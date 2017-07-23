#include "db/Log.hpp"
#include "util/Time.hpp"
using namespace CARDGAME;

string & MatchLog::GetQuery(string & user){
	query = "SELECT * FROM OP_MATCH_LOG_TB WHERE ";
	query+= "user_id1 = '" + user + "' OR ";
	query+= "user_id2 = '" + user + "'";
#ifdef ONEPOKER_DEBUG
	cout << "MatchLog select query : " << query << endl;
#endif
	return query;
}

string & MatchLog::WriteQuery(string & user1, string & user2, enum PLAYER winner){
	query = "INSERT INTO OP_MATCH_LOG_TB(user_id1, user_id2, winner, add_date) ";
	query+= "VALUES('" + user1 + "', '" + user2 + "' ";
	query+= (winner == PLAYER::PLAYER_1) ? ",'1'" :",'2'";
	query+= ", '" + GetTimeyyyymmdd() + "')";
#ifdef ONEPOKER_DEBUG
	cout << "MatchLog insert query : " << query << endl;
#endif
	return query;
}


string & AccessLog::GetQuery(string & user){
	query = "SELECT OP_USER_TB.id, OP_ACCESS_LOG_TB.ip, OP_ACCESS_LOG_TB.access_date ";
	query+= "FROM OP_ACCESS_LOG_TB INNER JOIN OP_USER_TB ON ";
	query+= "OP_USER_TB.id = '" + user + "' ";
	query+= "AND OP_USER_TB.user_num = OP_ACCESS_LOG_TB.user_num";
#ifdef ONEPOKER_DEBUG
	cout << "AccessLog select query : " << query << endl;
#endif
	return query;
}

string & AccessLog::WriteQuery(string & user, string & ip){
	query = "INSERT INTO OP_ACCESS_LOG_TB VALUES(";
	query+= "(SELECT user_num FROM OP_USER_TB WHERE id = '" + user + "')";
	query+= ",'" + ip + "'";
	query+= ",'" + GetTimeyyyymmdd() + "')";
#ifdef ONEPOKER_DEBUG
	cout << "AccessLog insert query : " << query << endl;
#endif
	return query;
}
