#include "db/GameSetting.hpp"
#include "util/DataBaseType.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;
using namespace ONEPOKER;

bool GameSetting::GetData(){
	if(DataBase::QueryRun(GetQuery()))
		return false;
	return true;
}

string & Rating::GetQuery(){
	query = "SELECT * FROM OP_RATING_TB";
#ifdef ONEPOKER_DEBUG
	cout << "Rating GetQuery : " << endl;
#endif
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
	query = "SELECT card_name, card_type, card_win FROM OP_CARD_LIST_TB";
#ifdef ONEPOKER_DEBUG
	cout << "CardList GetQuery : " << query << endl;
#endif
	return query;
}

bool CardList::InsertData(vector<string> & data){
	PokerCard card;
	if(data.size() != 3)
		return false;
	return true;
}

PokerCard CardList::GetRandomCard(){
	srand(time(NULL));
	int random_val = rand() % card_list.size();
#ifdef ONEPOKER_DEBUG
	cout << "CardList random val : " << random_val << endl;
#endif
	return card_list[random_val];
}
