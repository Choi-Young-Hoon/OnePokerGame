#include "db/DataBase.hpp"
#include "db/GameSetting.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace CARDGAME;

int main(void){
	if(DataBase::Connect("127.0.0.1", "root", "950214") 
			== OP_ERROR_FLAG::DB_CONNECT_ERROR)
		return -1;

	Rating * rating_list = Rating::GetInstance();
	if(!rating_list->GetData()){
		cout << "GetData() Error!!!!" << endl;
		DataBase::Close();
	}
	int money;

	while(1){
		cout << "Money : ";
		cin >> money;
		if(money == 0) break;

		cout << "Your rating : " << rating_list->FindRating(money) << endl;
	}
	DataBase::Close();
	return 0;
}
