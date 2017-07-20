#include "db/GameSetting.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace ONEPOKER;

bool GameSetting::GetData(){
	if(DataBase::QueryRun(GetQuery()))
		return false;
	return true;
}

string & Rating::GetQuery(){
	query = "";
	return query;
}

int Rating::FindRating(int money){
	query = "" + to_string(money);
	return 0;
}
