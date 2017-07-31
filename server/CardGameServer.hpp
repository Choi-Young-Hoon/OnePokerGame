#ifndef __ONEPOKER_SERVER_CARDGAME_HEADER__
#define __ONEPOKER_SERVER_CARDGAME_HEADER__
#include "server/ConnectorThread.hpp"
#include "server/LoginThread.hpp"
#include "server/Sync.hpp"
#include "db/BlackList.hpp"

namespace CARDGAME{
	class CardGameServer{
	public:
		CardGameServer(){}
		~CardGameServer(){}

		bool Init();
		void StartServerThread();
		bool ServerStart(int port);
		void ServerStop();
	private:
		int server_fd;
		Connector connector_worker;
		LoginThread login_worker;
		BlackIP * black_ip;		
	};
};

#endif
