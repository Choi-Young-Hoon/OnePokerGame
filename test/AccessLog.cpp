#include "db/Log.hpp"
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
	int select;
	bool successFlag;
	AccessLog log;
	while(1){
		cout << "======= AccessLog =======" << endl;
		cout << "1. Insert" << endl;
		cout << "2. Select" << endl;
		cout << "select : "; cin >> select;
		cout << "id : "; cin >> str;

		if(select == 1){
			cout << "ip : "; cin >> str2;
			successFlag = log.write_log(str, str2);
		} else if(select == 2){
			successFlag = log.get_log(str);
			while(successFlag && log.get_data(&data)){
				for(auto & iter : data)
					cout << iter << " ";
				cout << endl;
			}
		}
		else
			break;
		if(successFlag)
			cout << "Success" << endl;
		else
			cout << "Failed" << endl;
		successFlag = false;
	}


	DataBase::db_close();
	return 0;
}
