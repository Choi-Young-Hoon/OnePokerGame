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
	login_sync = LoginSync::GetInstance();
	if(login_sync == NULL)
		return false;

	parse_error_message = "PROTOCOL WRONG";
	return true;
}

bool Connector::AddClient(int sock_fd){
	if(epoll.AddFd(sock_fd) < 0)
		return false;
	return true;
}

bool Connector::DelClient(int sock_fd){
	if(epoll.DelFd(sock_fd) < 0)
		return false;
	return true;
}

void Connector::Action(int client_sock){
	map<string, string> & data = ServerThread::request_parsor.GetData();
	string response_message = "";
	UserData user_data;

	switch(ServerThread::request_parsor.GetMethod()){
		case USER_LOGIN: //로그인 처리.
#ifdef ONEPOKER_DEBUG
			cout << "USER_LOGIN 요청 처리중" << endl;
			cout << "받은 데이터 : " << data["user_id"] << " " << data["user_pwd"] << endl;
#endif
			if(ServerThread::user_db.Search(data["user_id"],
						data["user_pwd"], &user_data)){ //Success
#ifdef ONEPOKER_DEBUG
				cout << "USER 계정 인증 성공" << endl;
#endif
				if(user_data.IsCert()){
#ifdef ONEPOKER_DEBUG
					cout << "이메일 인증된 계정" << endl;
#endif
					response_message = "USER_LOGIN SUCCESS\n";
					response_message+= "user_id:" + user_data.GetId() + "\n";
				} else {
#ifdef ONEPOKER_DEBUG
					cout << "이메일 인증이 안된 계정" << endl;
#endif
					response_message = "USER_LOGIN FAILED\n";
					response_message+= "reason:emailcert";
				}
			} else {//Failed
				response_message = "USER_LOGIN FAILED";	
			}
			break;
		case USER_ADD: //가입 처리
#ifdef ONEPOKER_DEBUG
			cout << "가입 요청 처리" << endl;
#endif
			if(ServerThread::user_db.Insert(data["user_id"], 
						data["user_pwd"], data["user_email"])){ //Success
#ifdef ONEPOKER_DEBUG
				cout << "가입 요청 처리 성공" << endl;
#endif
				response_message = "USER_ADD SUCCESS\n";
				response_message += "user_email:" + data["user_email"];
			} else  {//Failed
#ifdef ONEPOKER_DEBUG
				cout << "가입 실패" << endl;
#endif
				response_message = "USER_ADD FAILED";
			}
			break;
	//	case USER_EMAIL_CERT: //유저 이메일 인증 처리
	//		break;
		default:
			response_message = parse_error_message;
	}
	send(client_sock, response_message.c_str(), response_message.length(), 0);
}

void Connector::Run(){
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
				if(!ServerThread::request_parsor.parse(recv_buf)){ //Protocol Error
					send(event_fd, parse_error_message.c_str(), 
							parse_error_message.length(), 0); 
					continue;
				}
				Action(event_fd);
			}
		} // Inner While
	} // Out While
}

