#include "server/LoginThread.hpp"
#include "server/ConnectorThread.hpp"
#include "db/User.hpp"
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
using namespace CARDGAME;

LinkList<int, map<string, string>> LoginThread::login_queue;

bool LoginThread::Init(){
#ifdef ONEPOKER_DEBUG
	cout << "LoginThread Initialize" << endl;
#endif
	login_sync = LoginSync::GetInstance();
	black_user = BlackUser::GetInstance();

	if(login_sync == NULL || black_user == NULL)
		return false;
	return true;
}

void LoginThread::Run(){
	int client_sock;
	map<string, string> client_data;
	string block_messaeg = "BLOCK", response_message = "";
	UserData user_data;

	while(true){
#ifdef ONEPOKER_DEBUG
		cout << "LoginThread Event wait" << endl;
		cout << "LoginQueue Count : " << login_queue.GetNodeCount() << endl;
#endif
		client_data.clear();
		//이벤트 대기
		while(login_queue.GetNodeCount() == 0){
#ifdef ONEPOKER_DEBUG
			cout << "Cond Wait()" << endl;
#endif
			login_sync->wait();
		}
		login_sync->unlock();
		client_sock = login_queue.GetFirstData();
		client_data = login_queue.GetSecondData();
		if(!login_queue.DelFrontNode()){
			cout << "LoginThread DelFrontNode() failed" << endl;
			exit(1);
		}
#ifdef ONEPOKER_DEBUG
		cout << "LoginThread GetData finish" << endl;
#endif
		//차단된 유저인지 확인.
		if(black_user->Search(client_data["user_id"])){
			if(!Connector::AddClient(client_sock))
				close(client_sock);
			else
				send(client_sock, block_messaeg.c_str(), block_messaeg.length(), 0);
			continue;
		}
#ifdef ONEPOKER_DEBUG
		cout << "차단된 유저 아님 : " << client_data["user_id"] << endl;
#endif
		//로그인 작업 처리.
		if(ServerThread::user_db.Search(client_data["user_id"], client_data["user_pwd"], &user_data)){
#ifdef ONEPOKER_DEBUG
			cout << "Login 인증 성공" << endl;
#endif
			//이메일 인증 확인.
			if(user_data.IsCert()){
#ifdef ONEPOKER_DEBUG
				cout << "Email 인증된 계정 " << user_data.GetId() << endl;
#endif
				response_message = "USER_LOGIN SUCCESS\n";
				response_message+= "user_id:" + user_data.GetId() + "\n";
			} else {
#ifdef ONEPOKER_DEBUG
				cout << "Email 인증되지 않은 계정" << endl;
#endif
				response_message = "USER_LOGIN FAILED\n";
				response_message+= "reason:emailcert";
				if(!Connector::AddClient(client_sock)){
					close(client_sock);
				}
			}
		} else { //로그인 실패
			response_message = "USER_LOGIN FAILED";
			if(!Connector::AddClient(client_sock)){
				close(client_sock);
			}
		}
#ifdef ONEPOKER_DEBUG
		cout << "Login Thread 결과 전송" << endl;
#endif
		if(send(client_sock, response_message.c_str(), response_message.length(), 0) == -1){
			cout << "LoginThread send() failed" << endl;
		}

	}//while
}

bool LoginThread::AddQueue(int sock_fd, map<string, string> data){
	if(!login_queue.AddNode(sock_fd, data))
		return false;
	//@TODO Error!!!!! 
//	login_sync->signal();
	LoginSync::GetInstance()->signal();
	return true;
}
