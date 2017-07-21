#include "db/GameSetting.hpp"
#include "util/DataBaseType.hpp"
#include "util/GameType.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace ONEPOKER;

Rating * Rating::instance = NULL;
CardList * CardList::instance = NULL;

bool GameSetting::GetData(){
	vector<string> data;
	if(DataBase::QueryRun(GetQuery()) &&
	   DataBase::GetResult()){
		while(DataBase::GetData(&data, DataBase::GetFieldCount()))
			InsertData(data);
		return true;
	}
	return false;
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
	card.SetCard((enum CARD_TYPE)GetCardData(data[CARD_LIST_TB::CARD_TYPE]) ,
		     (enum CARD)GetCardData(data[CARD_LIST_TB::CARD_NAME]) ,
		     (enum CARD)GetCardData(data[CARD_LIST_TB::CARD_WIN]));
	card_list.push_back(card);
	return true;
}

PokerCard CardList::GetRandomCard(){
	int random_val = rand() % card_list.size();
#ifdef ONEPOKER_DEBUG
	cout << "CardList random val : " << random_val << endl;
#endif
	return card_list[random_val];
}
