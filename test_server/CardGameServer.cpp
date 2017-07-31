#include "server/CardGameServer.hpp"
#include <iostream>
#include <string>
using namespace CARDGAME;
using namespace std;
int main(void){
	CardGameServer server;
	if(!server.Init()){
		cout << "Server Init() Failed" << endl;
		return -1;
	}

	server.StartServerThread();

	if(!server.ServerStart(30000)){
		cout << "Server Init() Failed" << endl;
		return -1;
	}

	server.ServerStop();
	return 0;
}

