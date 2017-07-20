#include "db/BlackList.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace ONEPOKER;

int main(void){
	if(DataBase::db_connect("127.0.0.1", "root", "950214")
			== OP_ERROR_FLAG::DB_CONNECT_ERROR)
		return -1;
	
	string str;
	bool successFlag;
	int select;
	BlackIP * inst = BlackIP::getInstance();
	
	while(1){
		cout << "======= BlackIP =======" << endl;
		cout << "1. Insert" << endl;
		cout << "2. Select" << endl;
		cout << "3. Delete" << endl;
		cout << "select : "; cin >> select;
		cout << "ip : "; cin >> str;

		if(select == 1)
			successFlag = inst->insert(str, "Test Data");
		else if(select == 2)
			successFlag = inst->search(str);
		else if(select == 3)
			successFlag = inst->remove(str);
		else
			break;
		
		cout << ((successFlag) ? "Success" : "Failed") << endl;
		successFlag = false;
	}
	DataBase::db_close();
	return 0;
}
