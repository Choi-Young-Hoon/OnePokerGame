#include "server/CardGameServer.hpp"
#include "server/Protocol.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
using namespace CARDGAME;


#ifdef ONEPOKER_DEBUG
#include <iostream>
using namespace std;
#endif

bool CardGameServer::Init(){
#ifdef ONEPOKER_DEBUG
	cout << "CardGameServer Initialize()" << endl;
#endif
	Protocol::InitProtocolData();
	blackIP = BlackIP::GetInstance();
	if(DataBase::Connect("127.0.0.1", "root", "950214")
			    == OP_ERROR_FLAG::DB_CONNECT_ERROR)
		return false;
	if(!connectorWorker.Init())
		return false;

	return true;
}

void CardGameServer::StartServerThread(){
	connectorWorker.start();
}

bool CardGameServer::ServerStart(int port){
#ifdef ONEPOKER_DEBUG
	cout << "ServerStart====================" << endl;
#endif
	int clientSock;
	struct sockaddr_in serv_addr, client_addr;
	socklen_t client_addr_size = sizeof(client_addr);
	string blockMessage = "BLOCK", errorMessage = "ERROR", joinMessage = "JOIN";

	memset(&serv_addr, 0x00, sizeof(serv_addr));
	
	serv_addr.sin_family = PF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	serverFd = socket(PF_INET, SOCK_STREAM, 0);
	if(serverFd == -1)
		return false;
	if(bind(serverFd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		return false;
	if(listen(serverFd, 10) == -1)
		return false;
	while(true){
#ifdef ONEPOKER_DEBUG
		cout << "Client Join Wait" << endl;
#endif
		clientSock = accept(serverFd, (struct sockaddr*)&client_addr, &client_addr_size);
		if(clientSock == -1)
			continue;
#ifdef ONEPOKER_DEBUG
		cout << "Client Join : " << inet_ntoa(client_addr.sin_addr) << endl;
#endif
		if(blackIP->Search(inet_ntoa(client_addr.sin_addr))){ //차단된 ip
#ifdef ONEPOKER_DEBUG
			cout << "Black IP : " << inet_ntoa(client_addr.sin_addr) << endl;
#endif
			send(clientSock, blockMessage.c_str(), blockMessage.length(), 0);
			close(clientSock);
		} else { //차단되지 않은 IP

#ifdef ONEPOKER_DEBUG
			cout << "JOIN IP : " << inet_ntoa(client_addr.sin_addr) << endl;
#endif
			if(!connectorWorker.AddClient(clientSock)){ //Connector 스레드로 넘김
#ifdef ONEPOKER_DEBUG
				cout << "ADD Connector " << endl;
#endif
				send(clientSock, errorMessage.c_str(), errorMessage.length(), 0);
				close(clientSock);
			} else {
				send(clientSock, joinMessage.c_str(), joinMessage.length(), 0);
			}
		}
	}
	return true;
}

void CardGameServer::ServerStop(){
#ifdef ONEPOKER_DEBUG
	cout << "Server Stop()!" << endl;
#endif
	connectorWorker.stop();
	close(serverFd);
	Protocol::Clear();
	DataBase::Close();
}


