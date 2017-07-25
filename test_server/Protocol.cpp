#include "server/Protocol.hpp"
#include <iostream>
#include <string>
#include <map>
using namespace std;
using namespace CARDGAME;

int main(void){
	Protocol::InitProtocolData();

	Protocol proto;
	string data = "user_id:agag\n"
		      "user_pwd:gaga";

	string search_data = "USER_LOGIN";
	enum PROTOCOL_METHOD method = proto.SearchMethod(search_data);
	search_data = "REQUEST";
	enum PROTOCOL_TYPE type = proto.SearchType(method, search_data);
	if(type == PROTOCOL_TYPE::TYPE_ERROR){
		cout << "Type Error" << endl;
		return -1;
	}
	cout << "Type : " << type << endl;

	map<string, string> parse_data = proto.GetData(data);
	for(auto iter = parse_data.begin(); iter != parse_data.end(); iter++)
		cout << iter->first << " " << iter->second << endl;

	Protocol::Clear();
	return 0;
}
