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
