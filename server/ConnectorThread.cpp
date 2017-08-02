#include "server/ConnectorThread.hpp"
#include "server/LoginThread.hpp"
#include "util/ServerSocket.hpp"
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

void Connector::Action(Socket & client_sock){
	map<string, string> & data = ServerThread::request_parsor.GetData();
	string response_message = "";
	UserData user_data;

	switch(ServerThread::request_parsor.GetMethod()){
		case USER_LOGIN: //로그인 처리.
#ifdef ONEPOKER_DEBUG
			cout << "[ConnectorThread] 로그인 요청 LoginThread로 넘김" << endl;
#endif
			//현재 Connector 스레드에서 해당 소켓 을제거.
			if(!DelClient(client_sock.GetSockFd())){
#ifdef ONEPOKER_DEBUG
				cout << "[ConnectorThread] ConnectorThread DelClient() Failed" << endl;
#endif
				client_sock.Close();
				response_message = "SERVER ERROR";
				break;
			}

			//로그인 큐에 추가.
			if(!LoginThread::AddQueue(client_sock.GetSockFd(), data)){
#ifdef ONEPOKER_DEBUG
				cout << "[ConnectorThread] AddQueue() Failed" << endl;
#endif
				response_message = "SERVER ERROR";
				break;
			}

			response_message = "LOGIN START";
			break;
		case USER_ADD: //가입 처리
#ifdef ONEPOKER_DEBUG
			cout << "[ConnectorThread] 가입 요청 처리" << endl;
#endif
			if(ServerThread::user_db.Insert(data["user_id"], 
						data["user_pwd"], data["user_email"])){ //Success
#ifdef ONEPOKER_DEBUG
				cout << "[ConnectorThread] 가입 요청 처리 성공" << endl;
#endif
				response_message = "USER_ADD SUCCESS\n";
				response_message += "user_email:" + data["user_email"];
			} else  {//Failed
#ifdef ONEPOKER_DEBUG
				cout << "[ConnectorThread] 가입 실패" << endl;
#endif
				response_message = "USER_ADD FAILED";
			}
			break;
	//	case USER_CERT: //유저 이메일 인증 및 비밀번호 찾기 처리
	//		break;
		default:
			response_message = parse_error_message;
	}
	client_sock.Write(response_message.c_str(), response_message.length());
}

void Connector::Run(){
	int event_fd = 0, recv_size = 0;
	char recv_buf[2048] = {0,};
	Socket sock;

	while(true){
		epoll.WaitEvent();
		while((event_fd = epoll.GetEventFd())){
			sock.SetSockFd(event_fd);
			recv_size = sock.Read(recv_buf, sizeof(recv_buf));
			if(recv_size <= 0) { //Client Close
				DelClient(event_fd);
				sock.Close();
			} else { //Client Request
#ifdef ONEPOKER_DEBUG
				cout << "[ConnectorThread] 받은 데이터" << endl;
				cout << recv_buf << endl;
#endif
				if(!ServerThread::request_parsor.parse(recv_buf)){ //Protocol Error
					sock.Write(parse_error_message.c_str(), 
							parse_error_message.length()); 
					continue;
				}
				Action(sock);
			}
		} // Inner While
	} // Out While
}

