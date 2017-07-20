#include "db/BlackList.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace ONEPOKER;

int main(void){
	if(DataBase::Connect("127.0.0.1", "root", "950214")
			== OP_ERROR_FLAG::DB_CONNECT_ERROR)
		return -1;
	
	string str;
	bool success_flag;
	int select;
	BlackIP * inst = BlackIP::GetInstance();
	
	while(1){
		cout << "======= BlackIP =======" << endl;
		cout << "1. Insert" << endl;
		cout << "2. Select" << endl;
		cout << "3. Delete" << endl;
		cout << "select : "; cin >> select;
		cout << "ip : "; cin >> str;

		if(select == 1)
			success_flag = inst->Insert(str, "Test Data");
		else if(select == 2)
			success_flag = inst->Search(str);
		else if(select == 3)
			success_flag = inst->Remove(str);
		else
			break;
		
		cout << ((success_flag) ? "Success" : "Failed") << endl;
		success_flag = false;
	}
	DataBase::Close();
	return 0;
}
