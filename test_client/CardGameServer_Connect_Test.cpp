#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

#include <iostream>
#include <string>
#include <thread>
using namespace std;

void RecvFunc(int sock){
	char buf[1024] = {0,};

	while(1){
		memset(buf, 0x00, 1024);
		recv(sock, buf,1024, 0);
		cout << "RECV=====================" << endl;
		cout << buf << endl;
	}
}
int main(void){
	int sockFd;
	struct sockaddr_in addr;
	string sendData;
	
	sendData = "USER_LOGIN REQUEST\n";
	sendData+= "user_id:hun5077\n";
	sendData+= "user_pwd:123123\n";
	sendData+= "email_cert:àçhauOÑW^ê";

	addr.sin_family = PF_INET;
	addr.sin_port = htons(30000);
	addr.sin_addr.s_addr = inet_addr("192.168.219.105");

	sockFd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockFd == -1){
		cout << "Socket() failed" << endl;
		return -1;
	}

	if(connect(sockFd, (struct sockaddr*)&addr, sizeof(addr)) == -1){
		cout << "Connect Failed "<< endl;
		return -1;
	}

	thread tt(RecvFunc, sockFd);
	for(int i = 0; i < 2; i++){
		if(send(sockFd, sendData.c_str(), sendData.length(), 0) == -1){
			cout << "Send() Failed" << endl;
			close(sockFd);
			return -1;
		}
		sleep(3);
	}
	
	tt.join();

	close(sockFd);
	return 0;
}
