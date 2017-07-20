#include "db/GameSetting.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace ONEPOKER;

bool GameSetting::get_data(){
	if(DataBase::db_query_run(getQuery()))
		return false;
	return true;
}

string & Rating::getQuery(){
	query = "";
	return query;
}

int Rating::find_rating(int money){
	query = "" + to_string(money);
	return 0;
}
