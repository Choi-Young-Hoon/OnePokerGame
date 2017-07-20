#include "db/Log.hpp"
#include "util/GameType.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace ONEPOKER;

int main(void){
	if(DataBase::db_connect("127.0.0.1", "root", "950214")
			== OP_ERROR_FLAG::DB_CONNECT_ERROR)
		return -1;

	string str, str2;
	vector<string> data;
	bool successFlag;
	int select;
	MatchLog log;
	while(1){
		cout << "======= MatchLog ======" << endl;
		cout << "1. Insert" << endl;
		cout << "2. Search" << endl;
		cout << "select : "; cin >> select;
		cout << "id : "; cin >> str;

		if(select == 1){ //Insert
			cout << "id2 : "; cin >> str2;
			cout << "Whos Win(1.Player1 2.Player2) : "; cin >> select;
			successFlag = log.write_log(str, str2,
				(select > 1) ? PLAYER::PLAYER1 : PLAYER::PLAYER2);
		} else if(select == 2){//Search
			successFlag = log.get_log(str);
			while(successFlag && log.get_data(&data)){
				for(auto & iter : data)
					cout << iter << " ";
				cout << endl;
			}
		} else
			break;

		if(successFlag)
			cout << "Success" << endl;
		else
			cout << "Failed" << endl;
		successFlag = false;
	}
	return 0;
}
