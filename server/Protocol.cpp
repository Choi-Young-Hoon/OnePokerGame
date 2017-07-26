#include "server/Protocol.hpp"
#include "util/TripleSearchTree.hpp"
#include "util/Protocol.hpp"
using namespace CARDGAME;
TripleSearchTree Protocol::method_tree;
TripleSearchTree Protocol::type_tree;

void Protocol::InitProtocolData(){
	method_tree.Insert("USER_LOGIN", PROTOCOL_METHOD::USER_LOGIN);
	method_tree.Insert("USER_ADD", PROTOCOL_METHOD::USER_ADD);
	method_tree.Insert("USER_DEL", PROTOCOL_METHOD::USER_DEL);
	method_tree.Insert("MATCH", PROTOCOL_METHOD::MATCH);
	method_tree.Insert("JOIN", PROTOCOL_METHOD::JOIN);
	method_tree.Insert("GAME", PROTOCOL_METHOD::GAME);

	type_tree.Insert("REQUEST", PROTOCOL_TYPE::REQUEST);
	type_tree.Insert("SUCCESS", PROTOCOL_TYPE::SUCCESS);
	type_tree.Insert("FAILED", PROTOCOL_TYPE::FAILED);
	type_tree.Insert("START", PROTOCOL_TYPE::START);
	type_tree.Insert("WAIT", PROTOCOL_TYPE::WAIT);
	type_tree.Insert("READY", PROTOCOL_TYPE::READY);
	type_tree.Insert("CARD", PROTOCOL_TYPE::CARD);
	type_tree.Insert("ORDER", PROTOCOL_TYPE::ORDER);
	type_tree.Insert("COMMAND", PROTOCOL_TYPE::COMMAND);
	type_tree.Insert("FINISH", PROTOCOL_TYPE::FINISH);
	type_tree.Insert("CHAT", PROTOCOL_TYPE::CHAT);
}

enum PROTOCOL_METHOD Protocol::SearchMethod(string & method){
	int ret_val = method_tree.Search((const char *)method.c_str());
	if(ret_val == -1)
		return PROTOCOL_METHOD::METHOD_ERROR;	
	return static_cast<enum PROTOCOL_METHOD>(ret_val);
}

enum PROTOCOL_TYPE Protocol::SearchType(enum PROTOCOL_METHOD method, string & type){
	int ret_val = type_tree.Search((const char *)type.c_str());
	if( (ret_val & method) && (ret_val != -1) )
		return static_cast<enum PROTOCOL_TYPE>(ret_val);
	return PROTOCOL_TYPE::TYPE_ERROR;
}

map<string, string> & Protocol::GetData(string & proto_data){
	const char * c_data = proto_data.c_str();
	string key = "", data = "";
#define KEY 10
#define DATA 20
#define NON 00
	int data_type = KEY;

	field_data.clear();
	while(*c_data != '\0'){
		if(data_type == KEY)
			key += *c_data;
		else if(data_type == DATA)
			data += *c_data;
		c_data++;
		if(*c_data == ':'){
			c_data++;
			data_type = DATA;
		}else if(*c_data == '\n' || *c_data == '\0'){
			if(data_type == KEY)
				break;
			data_type = KEY;
			field_data.insert(make_pair(key, data));
			key = data = "";
		}
	}
	return field_data;
}

void Protocol::Clear(){
	method_tree.Clear();
	type_tree.Clear();
}
