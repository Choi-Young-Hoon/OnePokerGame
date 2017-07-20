#include "db/User.hpp"
#include "util/Time.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace ONEPOKER;

int menu(void){
	int select = 0;
	cout << "======= User =======" << endl;
	cout << "1.Insert" << endl;
	cout << "2.Search" << endl;
	cout << "3.Delete" << endl;
	cout << "4.Update" << endl;
	cout << "select : "; cin >> select;
	return select;
}

int main(void){
	if(DataBase::db_connect("127.0.0.1", "root", "950214")
			== OP_ERROR_FLAG::DB_CONNECT_ERROR)
		return -1;

	int select;
	bool successFlag = false;
	bool userDataSet = false;
	UserData userData;
	User userDB;
	while(1){
		select = menu();
		if(select == 1){ //insert
			string id, pwd, email;
			cout << "id pwd email : "; cin >> id >> pwd >> email;
			successFlag = userDB.insert(id, pwd, email);
		} else if(select == 2){ //select
			string id, pwd;
			cout << "id pwd : "; cin >> id >> pwd;
			successFlag = userDataSet = userDB.search(id, pwd, &userData);
		} else if(select == 3){ //delete
			if(userDataSet)
				successFlag = userDB.remove(userData);
			else
				successFlag = false;
		} else if(select == 4){ //update
			if(userDataSet){
				string pwd, email;
				cout << "pwd email: "; cin >> pwd >> email;
				userData.setData(pwd, email);
				userData.setRecentDate(get_time_yyyymmdd());
				userData.setStat(100, true);
				successFlag = userDB.update(&userData);
			}else
				successFlag = false;
		} else
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
