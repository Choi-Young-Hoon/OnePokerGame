#include "server/Epoll.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <thread>
using namespace std;
using namespace CARDGAME;

int start_server(int * serv_sock){
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = PF_INET;
	serv_addr.sin_port = htons(10000);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	*serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(*serv_sock == -1)
		return -1;
	if(bind(*serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		return -1;
	if(listen(*serv_sock, 10) == -1)
		return -1;
	return 0;
}

int main(void){
	Epoll epoll;
	int serv_sock = 0;
	int event_fd = 0;
	char buff[1024] = {0,};
	struct sockaddr_in client_addr;
	socklen_t c_addr_size = sizeof(client_addr);
	
	if(start_server(&serv_sock)){
		cout << "start_server() error" << endl;
		if(serv_sock != 0)
			close(serv_sock);
	}

	if(epoll.Create(10) == -1){
		cout << "epoll create error" << endl;
		close(serv_sock);
		return -1;
	}
	if(epoll.AddFd(serv_sock) < 0){
		cout << "epoll AddFd error" << endl;
		epoll.Close(); close(serv_sock);
		return -1;
	}
	while(1){
		epoll.WaitEvent();
		while((event_fd = epoll.GetEventFd())){
			if(event_fd == serv_sock){
				int client_sock = 0;
				client_sock = accept(serv_sock, (struct sockaddr *)&client_addr, &c_addr_size);
				if(client_sock == -1)
					continue;
				epoll.AddFd(client_sock);
				epoll.BroadCastMessage("BroadCast JOIN", serv_sock);
			}
			else{
				switch(recv(event_fd, buff, 1024,0)){
					case 0:
						epoll.DelFd(event_fd);
						close(event_fd);
						cout << "DELETE" << endl;
						break;
					default:
						cout << "Recv : " << buff << endl;
						send(event_fd, "ttt", 3, 0);
				}
			}
		}
	}

	epoll.Close();
	return 0;
}
