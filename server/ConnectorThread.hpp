#ifndef __ONEPOKER_SERVER_CONNECTORTHREAD_HEADER__
#define __ONEPOKER_SERVER_CONNECTORTHREAD_HEADER__
#include "server/ServerThread.hpp"
#include "server/Epoll.hpp"
#include "server/Sync.hpp"
#include "util/ServerSocket.hpp"
#include <thread>
using namespace std;

namespace CARDGAME{
	/*
	 * 해당 Connector 쓰레드에서는 
	 * 회원가입, 암호 찾기, 이메일 인증, 로그인요청을 처리한다.
	 */
	class Connector : public ServerThread {
	public:
		Connector(){}
		~Connector(){}

		//해당 스레드에서 실제로 실행될 함수
		void Run();
		
		/*
		 * run 함수에서 받은 요청을 파싱한후 해당 요청을
		 * 처리하는 함수
		 * @param
		 * clientSock - 요청을한 클라이언트 소켓 디스크립터
		 */
		void Action(Socket & client_sock);
		
		/*
		 * 현재 스레드의 Epoll에 디스크립터 추가.
		 * @param
		 * sockFd - 추가할 소켓 디스크립터
		 * @return
		 * 성공시 true
		 * 실패시 false 
		 */
		static bool AddClient(int sock_fd);
		
		/*
		 * 현재 스레드의 Epoll에 디스스크립터 제거.
		 * @param
		 * sockFd - 제거할 소켓 디스크립터
		 * @return
		 * 성공시 true
		 * 실패시 false
		 */
		static bool DelClient(int sock_fd);
		
		
		virtual bool Init();
		virtual thread doWork(){
			return thread([=](){ Run(); });
		}
	private:
		static Epoll epoll;
		string parse_error_message;
		LoginSync * login_sync;
	};
};
#endif
