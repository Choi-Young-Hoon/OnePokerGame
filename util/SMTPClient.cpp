#include "util/SMTPClient.hpp"
using namespace CARDGAME;

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
bool SmtpClient::Connect(){
	struct sockaddr_in addr;

	addr.sin_family = PF_INET;
	addr.sin_port = htons(smtp_server_port);
	addr.sin_addr.s_addr = inet_addr(smtp_server_ip.c_str());

	sock_fd = socket(PF_INET, SOCK_STREAM, 0);
	if(sock_fd == -1)
		return false;
	if(connect(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1){
		close(sock_fd);
		return false;
	}
	return true;
}

bool SmtpClient::Close(){
	close(sock_fd);
}

bool SmtpClient::Send(){
	string smtp_data[]= {
		"HELO " + smtp_server_ip + "\r\n",
		"MAIL FROM: " + sender + "\r\n",
		"RCPT TO: " + receiver + "\r\n",
		"DATA\r\n",
		"SUBJECT: " + subject + "\r\n",
		data + "\r\n",
		".\r\n"};
	for(auto & data : smtp_data){
		if(send(sock_fd, data.c_str(), data.length(), 0) == -1)
			return false;
	}
	return true;
}
