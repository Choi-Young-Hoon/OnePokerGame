#ifndef __ONEPOKER_SERVER_SERVERTHRED_HEADAER__
#define __ONEPOKER_SERVER_SERVERTHRED_HEADAER__
#include <thread>
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
		void stop(){
			pthread_cancel(worker.native_handle());
		}
		virtual thread & doWork() = 0;
	private:
		thread worker;
	};
};
#endif
