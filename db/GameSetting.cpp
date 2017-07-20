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
	query = "SELECT * FROM OP_RATING_TB";
	return query;
}

bool Rating::InsertData(vector<string> & data){

	return true;
}

int Rating::FindRating(int money){
	query = "" + to_string(money);
	return 0;
}



string & CardList::GetQuery(){
	query = "SELECT * FROM OP_CARD_LIST_TB";
	return query;
}

bool CardList::InsertData(vector<string> & data){

	return true;
}

PokerCard CardList::GetRandomCard(){

}
