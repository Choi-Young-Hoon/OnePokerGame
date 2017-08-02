#include "server/LoginThread.hpp"
#include "server/ConnectorThread.hpp"
#include "server/WaitingThread.hpp"
#include "game/PokerUser.hpp"
#include "db/User.hpp"

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdlib>
#include <ctime>
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
	if(!smtp_client.Connect())
		return false;
	srand(time(NULL));
	return true;
}

/*
 * 이메일 인증키값 생성
 * 10자리
 */
static string GetCertkey(){
	string key = "";
	for(int i = 0; i < 10; i++)
		key += (char)(rand() % 'Z' + 'A');
	return key;
}
void LoginThread::Run(){
	Socket client_sock;
	map<string, string> client_data;
	string block_messaeg = "BLOCK", response_message = "";
	UserData user_data;

	while(true){
#ifdef ONEPOKER_DEBUG
		cout << "[LoginThread] LoginThread Event wait" << endl;
		cout << "[LoginThread] LoginQueue Count : " << login_queue.GetNodeCount() << endl;
#endif
		client_data.clear();
		//이벤트 대기
		while(login_queue.GetNodeCount() == 0){
#ifdef ONEPOKER_DEBUG
			cout << "[LoginThread] Cond Wait()" << endl;
#endif
			login_sync->wait();
		}
		login_sync->unlock();
		client_sock.SetSockFd(login_queue.GetFirstData());
		client_data = login_queue.GetSecondData();
		if(!login_queue.DelFrontNode()){
			cout << "LoginThread DelFrontNode() failed" << endl;
			exit(1);
		}
#ifdef ONEPOKER_DEBUG
		cout << "[LoginThread] LoginThread GetData finish" << endl;
#endif
		//차단된 유저인지 확인.
		if(black_user->Search(client_data["user_id"])){
			if(!Connector::AddClient(client_sock.GetSockFd()))
				client_sock.Close();
			else
				client_sock.Write(block_messaeg.c_str(), block_messaeg.length());
			continue;
		}
#ifdef ONEPOKER_DEBUG
		cout << "[LoginThread] 차단된 유저 아님 : " << client_data["user_id"] << endl;
#endif
		//로그인 작업 처리.
		if(ServerThread::user_db.Search(client_data["user_id"], client_data["user_pwd"], &user_data)){
#ifdef ONEPOKER_DEBUG
			cout << "[LoginThread] Login 인증 성공" << endl;
#endif
			if(client_data.find("email_cert") != client_data.end()){
				if(client_data["email_cert"] 
						== user_cert_key[user_data.GetNum()]){
					user_cert_key.erase(user_cert_key.find(user_data.GetNum()));
					ServerThread::user_db.Update(&user_data);
					user_data.SetEmailCert(true);
				}
			}
			//이메일 인증 확인.
			if(user_data.IsCert()){
#ifdef ONEPOKER_DEBUG
				cout << "[LoginThread] Email 인증된 계정 " << user_data.GetId() << endl;
#endif
				PokerUser user;
				user.SetUserData(user_data);
				if(!WaitingThread::AddClient(client_sock.GetSockFd(), user)){
					client_sock.Close();
				}

				response_message = "USER_LOGIN SUCCESS\n";
				response_message+= "user_id:" + user_data.GetId() + "\n";
			} else {
#ifdef ONEPOKER_DEBUG
				cout << "[LoginThread] Email 인증되지 않은 계정" << endl;
#endif
				response_message = "USER_LOGIN FAILED\n";
				response_message+= "reason:emailcert\n";
				response_message+= "user_email:" + user_data.GetEmail();
				
				smtp_client.SetSubject("CardGame Cert Key");
				smtp_client.SetSender("admin@cardgame.com");
				smtp_client.SetReceiver(user_data.GetEmail());
				smtp_client.SetData("Hello\nKey : " + GetCertkey());
				smtp_client.Send();
				
				if(!Connector::AddClient(client_sock.GetSockFd())){
					client_sock.Close();
				}
			}
		} else { //로그인 실패
			response_message = "USER_LOGIN FAILED";
			if(!Connector::AddClient(client_sock.GetSockFd())){
				client_sock.Close();
			}
		}
#ifdef ONEPOKER_DEBUG
		cout << "[LoginThread] Login Thread 결과 전송" << endl;
#endif
		if(client_sock.Write(response_message.c_str(), response_message.length()) == -1){
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
