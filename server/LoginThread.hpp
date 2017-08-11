#ifndef __ONEPOKER_SERVER_LOGINTHREAD_HEADER__
#define __ONEPOKER_SERVER_LOGINTHREAD_HEADER__
#include "server/ServerThread.hpp"
#include "server/Sync.hpp"
#include "db/BlackList.hpp"
#include "util/LinkList.hpp"
#include "util/ServerSocket.hpp"
#include "util/SMTPClient.hpp"

#include <string>
#include <map>
using namespace std;
namespace CARDGAME{
	class LoginThread : public ServerThread {
	public:
		LoginThread(){}
		~LoginThread(){}
	
		/*
		 * 해당 스레드에서 실제 실행될 함수
		 */
		void Run();
		
		/*
		 * 이메일 인증 키값을 전송한다.
		 */
		void SendEmailRegisterKey(string email, string key);	
		
		/*
		 * 로그인 큐에 추가한다.
		 * @param
		 * sock_fd - 클라이언트의 소켓 디스크립터.
		 * data - 클라이언트의 로그인 요청 정보 map
		 * @return
		 * 성공시 - true
		 * 실패시 - false
		 */
		static bool AddQueue(int sock_fd, map<string, string> data);

		virtual bool Init();
		virtual thread doWork(){
			return thread([=](){ Run(); });
		}
	private:
		static LinkList<int, map<string, string>> login_queue;
		map<int, string> user_cert_key;
		LoginSync * login_sync;
		BlackUser * black_user;
		SmtpClient smtp_client;
	};
};
#endif
