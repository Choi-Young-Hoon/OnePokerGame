#include <iostream>
#include <string>
using namespace std;

#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int main(void){
	int sock_fd;
	struct sockaddr_in sock_addr;
	char buf[1024] = "Hello World\n";
	
	sock_addr.sin_family = PF_INET;
	sock_addr.sin_port = htons(10000);
	sock_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	sock_fd = socket(PF_INET, SOCK_STREAM, 0);
	if(sock_fd == -1)
		return -1;
	
	if(connect(sock_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) == -1){
		close(sock_fd);
		return -1;
	}

	send(sock_fd, buf, 1024, 0);
	memset(buf, 0x00, 1024);
	recv(sock_fd, buf, 1024, 0);
	cout << buf << endl;
	for(int i = 0; i < 10; i++){
		memset(buf, 0x00, 1024);
		if(recv(sock_fd, buf, 1024, 0) == -1)
			return -1;
		cout << buf << endl;
	}
	close(sock_fd);
	return 0;
}
