#include "server/ProtocolRequest.hpp"
#include <string>
using namespace std;
using namespace CARDGAME;

int main(void){
	string data = "USER_AD REQUEST\n"
		      "user_id:HelloWorld\n"
		      "user_pwd:tesfsefsf";

	Protocol::InitProtocolData();
	ProtocolRequest test;
	if(!test.parse(data)){
		cout << "Parse Failed" << endl;
		Protocol::Clear();
		return 0;
	}
	Protocol::Clear();
	return 0;
}
