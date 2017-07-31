#ifndef __ONEPOKER_UTIL_SERVERSOCK_HEADER__
#define __ONEPOKER_UTIL_SERVERSOCK_HEADER__
#include <sys/socket.h>
#include <sys/types.h>
#include <openssl/ssl.h>

namespace CARDGAME {
	class Socket {
	public:
		Socket(){}
		~Socket(){}
		
		inline bool MakeSock(){
			sock_fd = socket(PF_INET, SOCK_STREAM, 0);
			if(sock_fd == -1)
				return false;
			return true;
		}

		inline int GetSockFd(){ return sock_fd; }
		inline void SetSockFd(int fd){ sock_fd = fd; }
	private:
		int sock_fd;
	};
};
#endif
