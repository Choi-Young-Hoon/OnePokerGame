#include "db/User.hpp"
#include "util/Time.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace CARDGAME;

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
	if(DataBase::Connect("127.0.0.1", "root", "950214")
			== OP_ERROR_FLAG::DB_CONNECT_ERROR)
		return -1;

	int select;
	bool success_flag = false;
	bool user_data_set = false;
	UserData user_data;
	User user_db;
	while(1){
		select = menu();
		if(select == 1){ //insert
			string id, pwd, email;
			cout << "id pwd email : "; cin >> id >> pwd >> email;
			success_flag = user_db.Insert(id, pwd, email);
		} else if(select == 2){ //select
			string id, pwd;
			cout << "id pwd : "; cin >> id >> pwd;
			success_flag = user_data_set = user_db.Search(id, pwd, &user_data);
		} else if(select == 3){ //delete
			if(user_data_set)
				success_flag = user_db.Remove(user_data);
			else
				success_flag = false;
		} else if(select == 4){ //update
			if(user_data_set){
				string pwd, email;
				cout << "pwd email: "; cin >> pwd >> email;
				user_data.SetData(pwd, email);
				user_data.SetRecentDate(GetTimeyyyymmdd());
				user_data.SetStat(100, true);
				success_flag = user_db.Update(&user_data);
			}else
				success_flag = false;
		} else
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
