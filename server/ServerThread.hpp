#ifndef __ONEPOKER_SERVER_SERVERTHRED_HEADAER__
#define __ONEPOKER_SERVER_SERVERTHRED_HEADAER__
#include "server/ProtocolRequest.hpp"
#include "db/User.hpp"
#include <pthread.h>
#include <thread>
#include <string>
using namespace std;

namespace CARDGAME{
	class ServerThread{
	public:
		ServerThread(){}
		~ServerThread(){}
		
		void start(){
			worker = doWork();
		}

		void wait(){
			worker.join();
		}

		void stop(){
			pthread_cancel(worker.native_handle());
			worker.join();
		}

		virtual bool Init() = 0;
		virtual thread doWork() = 0;
		
		thread worker;
		ProtocolRequest request_parsor;
		User user_db;
	};
};
#endif
