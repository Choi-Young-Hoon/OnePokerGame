#include "server/WaitingThread.hpp"
#include "util/Protocol.hpp"
using namespace CARDGAME;

#ifdef ONEPOKER_DEBUG
#include <iostream>
#endif
#include <map>
using namespace std;

Epoll WaitingThread::epoll;
map<int, PokerUser> WaitingThread::user_map;

bool WaitingThread::Init(){
#ifdef ONEPOKER_DEBUG
	cout << "WaitingThread Initialize" << endl;
#endif
	match_sync = MatchSync::GetInstance();
	if(match_sync == NULL)
		return false;
	if(epoll.Create(100) == -1)
		return false;
	return true;
}

/*
 * 유저에게 해당 유저의 정보를 보낸다.
 * @param
 * user_sock - 유저 소켓
 * user_data - 유저의 데이터.
 * @return
 * 성공시 - true
 * 실패시 - false
 */
static bool SendUserInfo(Socket & user_sock, UserData * user_data){
	string send_info = "";

	send_info = "USER_INFO\n";
	send_info+= "user_id:" + user_data->GetId() + "\n";
	send_info+= "user_money:" + to_string(user_data->GetMoney()) + "\n";
	send_info+= "user_win:" + to_string(user_data->GetWin()) + "\n";
	send_info+= "user_lose:" + to_string(user_data->GetLose());
	
	if(user_sock.Write(send_info.c_str(), send_info.length()) == -1)
		return false;
	return true;
}

bool WaitingThread::AddClient(int sock_fd, PokerUser & poker_user){
	if(epoll.AddFd(sock_fd) < 0)
		return false;
	
	string send_info = "";
	UserData * user_data = poker_user.GetUserData();
	Socket sock(sock_fd);
	
	user_map.insert(make_pair(sock_fd, poker_user));
	if(!SendUserInfo(sock, user_data)){
		DelClient(sock.GetSockFd());
		close(sock.GetSockFd());
		return false;
	}
	return true;
}

bool WaitingThread::DelClient(int sock_fd){
	if(epoll.DelFd(sock_fd) < 0)
		return false;
	auto user_iter = user_map.find(sock_fd);
	if(user_iter == user_map.end()) // Map 에 들어있지 않음
		return false;
	user_map.erase(user_iter);
	return true;
}

void WaitingThread::Action(Socket & client_sock){
	map<string, string> & data = ServerThread::request_parsor.GetData();
	string response_message = "";
	UserData userData;

	switch(ServerThread::request_parsor.GetMethod()){
		case PROTOCOL_METHOD::MATCH:
			if(ServerThread::request_parsor.GetType() 
					!= PROTOCOL_TYPE::START){
				response_message = "MATCH FAILED";
				break;
			}
			break;
		case PROTOCOL_METHOD::USER_CERT:	//자신의 정보 요청
			if(!SendUserInfo(client_sock, 
					user_map[client_sock.GetSockFd()].GetUserData())){
				DelClient(client_sock.GetSockFd());
				client_sock.Close();
				return;
			}
				break;
		default:
			response_message = "PROTOCOL ERROR";
	}
	client_sock.Write(response_message.c_str(), response_message.length());
}

void WaitingThread::Run(){
	int event_fd = 0, recv_size = 0;
	char recv_buf[2048] = {0,};
	Socket sock;
#ifdef ONEPOKER_DEBUG
	cout << "WaitingThread Run()" << endl;
#endif
	while(true){
		epoll.WaitEvent();
		while((event_fd = epoll.GetEventFd())){
			sock.SetSockFd(event_fd);
			recv_size = sock.Read(recv_buf, sizeof(recv_buf));
			if(recv_size <= 0){ //Close Client
				DelClient(event_fd);
				sock.Close();
			} else { //Client Request
#ifdef ONEPOKER_DEBUG
				cout << "[WaitingThread] 받은 데이터 " << endl;
				cout << recv_buf << endl;
#endif
				if(!ServerThread::request_parsor.parse(recv_buf)){ //Protocol Error
#ifdef ONEPOKER_DEBUG
					cout << "[WaitingThread] Parse Error" << endl;
#endif
					continue;	
				}
				//Protocol 파싱후 처리
				Action(sock);
			}
		}// Inner While
	}// Out While
}
