#include "server/ConnectorThread.hpp"
using namespace CARDGAME;

#include <string>
#include <map>
#include <iostream>
using namespace std;

Epoll Connector::epoll;

bool Connector::Init(){
	if(epoll.Create(100) == -1)
		return false;
	loginSync = LoginSync::GetInstance();
	if(loginSync == NULL)
		return false;

	parse_error_message = "PROTOCOL WRONG";
	return true;
}

bool Connector::AddClient(int sockFd){
	if(epoll.AddFd(sockFd) < 0)
		return false;
	return true;
}

bool Connector::DelClient(int sockFd){
	if(epoll.DelFd(sockFd) < 0)
		return false;
	return true;
}

void Connector::Action(int clientSock){
	map<string, string> & data = ServerThread::requestParsor.GetData();
	string responseMessage = "";
	UserData userData;

	switch(ServerThread::requestParsor.GetMethod()){
		case USER_LOGIN: //로그인 처리.
#ifdef ONEPOKER_DEBUG
			cout << "USER_LOGIN 요청 처리중" << endl;
			cout << "받은 데이터 : " << data["user_id"] << " " << data["user_pwd"] << endl;
#endif
			if(ServerThread::userDB.Search(data["user_id"],
						data["user_pwd"], &userData)){ //Success
#ifdef ONEPOKER_DEBUG
				cout << "USER 계정 인증 성공" << endl;
#endif
				if(userData.IsCert()){
#ifdef ONEPOKER_DEBUG
					cout << "이메일 인증된 계정" << endl;
#endif
					responseMessage = "USER_LOGIN SUCCESS\n";
					responseMessage+= "user_id:" + userData.GetId() + "\n";
				} else {
#ifdef ONEPOKER_DEBUG
					cout << "이메일 인증이 안된 계정" << endl;
#endif
					responseMessage = "USER_LOGIN FAILED\n";
					responseMessage+= "reason:emailcert";
				}
			} else {//Failed
				responseMessage = "USER_LOGIN FAILED";	
			}
			break;
		case USER_ADD: //가입 처리
#ifdef ONEPOKER_DEBUG
			cout << "가입 요청 처리" << endl;
#endif
			if(ServerThread::userDB.Insert(data["user_id"], 
						data["user_pwd"], data["user_email"])){ //Success
#ifdef ONEPOKER_DEBUG
				cout << "가입 요청 처리 성공" << endl;
#endif
				responseMessage = "USER_ADD SUCCESS\n";
				responseMessage += "user_email:" + data["user_email"];
			} else  {//Failed
#ifdef ONEPOKER_DEBUG
				cout << "가입 실패" << endl;
#endif
				responseMessage = "USER_ADD FAILED";
			}
			break;
	//	case USER_EMAIL_CERT: //유저 이메일 인증 처리
	//		break;
		default:
			responseMessage = parse_error_message;
	}
	send(clientSock, responseMessage.c_str(), responseMessage.length(), 0);
}

void Connector::run(){
	int event_fd = 0, recv_size = 0;
	char recv_buf[2048] = {0,};
	
	while(true){
		epoll.WaitEvent();
		while((event_fd = epoll.GetEventFd())){
			recv_size = recv(event_fd, recv_buf, 2048, 0);
			if(recv_size <= 0) { //Client Close
				DelClient(event_fd);
				close(event_fd);
			} else { //Client Request
#ifdef ONEPOKER_DEBUG
				cout << "받은 데이터" << endl;
				cout << recv_buf << endl;
#endif
				if(!ServerThread::requestParsor.parse(recv_buf)){ //Protocol Error
					send(event_fd, parse_error_message.c_str(), 
							parse_error_message.length(), 0); 
					continue;
				}
				Action(event_fd);
			}
		} // Inner While
	} // Out While
}

