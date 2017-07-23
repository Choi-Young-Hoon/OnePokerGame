#include "db/Log.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace CARDGAME;

int main(void){
	if(DataBase::Connect("127.0.0.1", "root", "950214")
			== OP_ERROR_FLAG::DB_CONNECT_ERROR)
		return -1;

	string str, str2;
	vector<string> data;
	int select;
	bool success_flag;
	AccessLog log;
	while(1){
		cout << "======= AccessLog =======" << endl;
		cout << "1. Insert" << endl;
		cout << "2. Select" << endl;
		cout << "select : "; cin >> select;
		cout << "id : "; cin >> str;

		if(select == 1){
			cout << "ip : "; cin >> str2;
			success_flag = log.WriteLog(str, str2);
		} else if(select == 2){
			success_flag = log.GetLog(str);
			while(success_flag && log.GetData(&data)){
				for(auto & iter : data)
					cout << iter << " ";
				cout << endl;
			}
		}
		else
			break;
		if(success_flag)
			cout << "Success" << endl;
		else
			cout << "Failed" << endl;
		success_flag = false;
	}


	DataBase::Close();
	return 0;
}
