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

	//Singleton Initialize
	black_ip = BlackIP::GetInstance();
	LoginSync::GetInstance()->init();
	MatchSync::GetInstance()->init();

	if(DataBase::Connect("127.0.0.1", "root", "950214")
			    == OP_ERROR_FLAG::DB_CONNECT_ERROR)
		return false;
	if(!connector_worker.Init() ||
	   !login_worker.Init())
		return false;

	return true;
}

void CardGameServer::StartServerThread(){
	connector_worker.start();
	login_worker.start();
}

bool CardGameServer::ServerStart(int port){
#ifdef ONEPOKER_DEBUG
	cout << "ServerStart====================" << endl;
#endif
	int client_sock;
	struct sockaddr_in serv_addr, client_addr;
	socklen_t client_addr_size = sizeof(client_addr);
	string block_message = "BLOCK", error_message = "ERROR", join_message = "JOIN";

	memset(&serv_addr, 0x00, sizeof(serv_addr));
	
	serv_addr.sin_family = PF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	server_fd = socket(PF_INET, SOCK_STREAM, 0);
	if(server_fd == -1)
		return false;
	if(bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		return false;
	if(listen(server_fd, 10) == -1)
		return false;
	while(true){
#ifdef ONEPOKER_DEBUG
		cout << "Client Join Wait" << endl;
#endif
		client_sock = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_size);
		if(client_sock == -1)
			continue;
#ifdef ONEPOKER_DEBUG
		cout << "Client Join : " << inet_ntoa(client_addr.sin_addr) << endl;
#endif
		if(black_ip->Search(inet_ntoa(client_addr.sin_addr))){ //차단된 ip
#ifdef ONEPOKER_DEBUG
			cout << "Black IP : " << inet_ntoa(client_addr.sin_addr) << endl;
#endif
			send(client_sock, block_message.c_str(), block_message.length(), 0);
			close(client_sock);
		} else { //차단되지 않은 IP

#ifdef ONEPOKER_DEBUG
			cout << "JOIN IP : " << inet_ntoa(client_addr.sin_addr) << endl;
#endif
			if(!connector_worker.AddClient(client_sock)){ //Connector 스레드로 넘김
#ifdef ONEPOKER_DEBUG
				cout << "ADD Connector " << endl;
#endif
				send(client_sock, error_message.c_str(), error_message.length(), 0);
				close(client_sock);
			} else {
				send(client_sock, join_message.c_str(), join_message.length(), 0);
			}
		}
	}
	return true;
}

void CardGameServer::ServerStop(){
#ifdef ONEPOKER_DEBUG
	cout << "Server Stop()!" << endl;
#endif
	connector_worker.stop();
	login_worker.stop();
	close(server_fd);
	Protocol::Clear();
	DataBase::Close();

	//Singleton Destroy
	LoginSync::GetInstance()->destroy();
	MatchSync::GetInstance()->destroy();
}


