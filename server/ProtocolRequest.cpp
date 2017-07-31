#include "server/ProtocolRequest.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace CARDGAME;

bool ProtocolRequest::GetMethodString(string & method, string & data){
	for(unsigned int i = 0; i < data.length(); i++){
		if(data[i] == ' '){
			method = data.substr(0, i);
			data = data.substr(i + 1, data.length());
			return true;
		}
		else if(data[i] == '\n')
			break;
	}
	return false;
}

bool ProtocolRequest::GetTypeString(string & type, string & data){
	for(unsigned int i = 0; i < data.length(); i++){
		if( (data[i] == '\n') && (i > 0) ){
			type = data.substr(0, i);
			data = data.substr(i + 1, data.length());
			return true;
		}
	}
	return false;
}

bool ProtocolRequest::parse(string data){
	string parse_method;
	string parse_type;

	if(!GetMethodString(parse_method, data) || 
	   !GetTypeString(parse_type, data))
		return false;
	
	this->method = Protocol::SearchMethod(parse_method);
	if(this->method == PROTOCOL_METHOD::METHOD_ERROR)
		return false;
	this->type = Protocol::SearchType(this->method, parse_type);
	if(this->type == PROTOCOL_TYPE::TYPE_ERROR)
		return false;
	this->data = Protocol::GetData(data);
#ifdef ONEPOKER_DEBUG
	cout << "파싱 데이터 출력 " << endl;
	for(auto iter = this->data.begin(); iter != this->data.end(); iter++)
		cout << iter->first << " " << iter->second << endl;
#endif
	return true;
}
