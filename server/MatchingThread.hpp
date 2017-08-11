#ifndef __ONEPOKER_SERVER_MATCHINGTHREAD_HEADER__
#define __ONEPOKER_SERVER_MATCHINGTHREAD_HEADER__
#include "server/ServerThread.hpp"
#include "server/Sync.hpp"
#include "game/PokerUser.hpp"
#include "util/GameType.hpp"
#include "util/LinkList.hpp"
#include <map>
#include <vector>
using namespace std;

namespace CARDGAME {
	class MatchingThread : public ServerThread{
	public:
		MatchingThread(){}
		~MatchingThread(){}
		
		bool StartGame(enum GAME_MODE mode, LinkList<int, PokerUser> user_list);
		inline bool DelQueue(enum GAME_MODE mode);
		bool DelQueue(enum GAME_MODE mode, int count);
		static bool AddQueue(enum GAME_MODE, int sock_fd, PokerUser & user);
		enum GAME_MODE CheckClientQueueCount(int need_client_count);
		void Run();

		virtual bool Init();
		virtual thread doWork(){
			return thread([=](){ Run(); });
		}
	private:
		//vector <GameMode>
		//LinkList<ClientSocketDescriptor, PokerUser>
		static vector<LinkList<int, PokerUser>> user_queue;
		MatchSync * match_cond;
	};
};
#endif
