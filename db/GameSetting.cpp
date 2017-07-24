#include "db/GameSetting.hpp"
#include "util/DataBaseType.hpp"
#include "util/GameType.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace CARDGAME;

Rating * Rating::instance = NULL;
CardList * CardList::instance = NULL;

bool GameSetting::GetData(){
	vector<string> data;
	if(DataBase::QueryRun(GetQuery()) &&
	   DataBase::GetResult()){
		while(DataBase::GetData(&data, DataBase::GetFieldCount())){
			if(!InsertData(data))
				return false;
		}
		return true;
	}
	return false;
}

string & Rating::GetQuery(){
	query = "SELECT rating_name, rating_condition FROM OP_RATING_TB";
#ifdef ONEPOKER_DEBUG
	cout << "Rating GetQuery : " << endl;
#endif
	return query;
}

bool Rating::InsertData(vector<string> & data){
	if(data.size() != 2)
		return false;
	rating_list.insert(make_pair(atoi(data[RATING_TB::RATING_NAME].c_str()), 
				     atoi(data[RATING_TB::RATING_CONDITION].c_str())));
	return true;
}

int Rating::FindRating(int money){
	int before = rating_list.size();
#ifdef ONEPOKER_DEBUG
		cout << "FindRating now money : " << money << endl;
#endif
	for(auto & iter : rating_list){
		if(money > iter.second){
			before = iter.first;
			break;
		}
#ifdef ONEPOKER_DEBUG
		cout << "FindRating first : " << iter.first << 
			"\tsecond : " << iter.second << endl;
#endif
		before = iter.first;
	}
	return before;
}



string & CardList::GetQuery(){
	query = "SELECT card_name FROM OP_CARD_LIST_TB";
#ifdef ONEPOKER_DEBUG
	cout << "CardList GetQuery : " << query << endl;
#endif
	return query;
}

bool CardList::InsertData(vector<string> & data){
#ifdef ONEPOKER_DEBUG
	cout << "CardList InsertData : " << data[CARD_LIST_TB::CARD_NAME] << endl;
#endif
	card_list.push_back( data[CARD_LIST_TB::CARD_NAME] );
	return true;
}

vector<string> &  CardList::GetCardList(){
	return card_list;
}
