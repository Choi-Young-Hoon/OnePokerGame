#ifndef __ONEPOKER_SERVER_WAITINGTHREAD_HEADER__
#define __ONEPOKER_SERVER_WAITINGTHREAD_HEADER__
#include "server/ConnectorThread.hpp"
#include "server/Epoll.hpp"
#include "server/Sync.hpp"
#include <map>

namespace CARDGAME {
	class WaitingThread : public ConnectorThread {
	public:
		WaitingThread(){}
		~WaitingThread(){}
		
		/*
		 * WaitingThread 에 유저를 추가한다.
		 * @param
		 * sock_fd - 클라이언트 소켓 디스크립터.
		 * poker_user - 유저의 정보
		 * @return
		 * 성공시 - true
		 * 실패시 - false
		 */
		static bool AddClient(int sock_fd, PokerUser & poker_user);
		
		/*
		 * 현재 스레드에서 유저를 제거한다.
		 * @param
		 * sock_fd - 클라이언트 소켓 디스크립터
		 * @return
		 * 성공시 - true
		 * 실패시 - false
		 */
		static bool DelClient(int sock_fd);

		//해당 스레드에서 실행될 함수.
		void Run();

		virtual bool Init();
		virtual thread doWork(){
			return thread([=](){ Run(); });
		}
	private:
		static Epoll epoll;
		static map<int, PokerUser> user_map;
		MatchSync * match_sync;
	};
};
#endif
