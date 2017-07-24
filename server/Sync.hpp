#ifndef __ONEPOKER_SERVER_SYNC_HEADER__
#define __ONEPOKER_SERVER_SYNC_HEADER__
#include <pthread.h>

namespace CARDGAME{
	class Sync{
	public:
		Sync(){}
		~Sync(){}

		void init(){
			pthread_mutex_init(&mutex, NULL);
			pthread_cond_init(&cond, NULL);
		}

		inline void destroy(){
			pthread_mutex_destory(&mutex);
			pthread_cond_destroy(&cond);
		}

		inline void wait(){
			pthread_mutex_lock(&mutex);
			pthread_cond_wait(&cond, &mutex);
		}
		
		inline void unlock(){
			pthread_mutex_unlock(&mutex);
		}

		inline void signal(){
			pthread_cond_signal(&cond);
		}
	private:
		pthread_mutex_t mutex;
		pthread_cond_t cond;
	};

	class LoginSync : public Sync {
	public:
		~LoginSync(){}
		static LoginSync * GetInstance(){
			if(instance == NULL)
				instance = new LoginSync();
			return instance;
		}
	private:
		LoginSync(){}
		static LoginSync * instance;

	};

	class MatchSync : public Sync {
	public:
		~MatchSync(){}
		static MatchSync * GetInstance(){
			if(instance == NULL)
				instance = new MatchSync();
			return instance;
		}
	private:
		MatchSync(){}
		static MatchSync * instance;
	};
};

#endif
