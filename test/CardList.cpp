#include "db/DataBase.hpp"
#include "db/GameSetting.hpp"
#include "util/DataBaseType.hpp"
#include "util/GameType.hpp"
#include "game/PokerCard.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace CARDGAME;

int main(void){
	if(DataBase::Connect("127.0.0.1", "root", "950214") 
			== OP_ERROR_FLAG::DB_CONNECT_ERROR)
		return -1;
	CardDataMapInit();

	vector<string> card_data;;
	CardList * card_list = CardList::GetInstance();
	
	cout << "Get card : " << endl;
	card_list->GetData();
	card_data = card_list->GetCardList();
	for(auto & i : card_data)
		cout << i << endl;
	DataBase::Close();
	return 0;
}
