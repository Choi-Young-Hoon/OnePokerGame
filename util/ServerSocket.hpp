#ifndef __ONEPOKER_UTIL_SERVERSOCK_HEADER__
#define __ONEPOKER_UTIL_SERVERSOCK_HEADER__
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace CARDGAME {
	class Socket {
	public:
		Socket(){}
		Socket(int fd) : sock_fd(fd){}
		~Socket(){}
	
		//Socket 생성.
		inline bool MakeSock(){
			sock_fd = socket(PF_INET, SOCK_STREAM, 0);
			if(sock_fd == -1)
				return false;
			return true;
		}

		inline int Read(char * buffer, const size_t buffer_size){
			return recv(sock_fd, buffer, buffer_size, 0);
		}
		inline int Write(const char * buffer, const size_t str_len){
			return send(sock_fd, buffer, str_len, 0);
		}
		inline void Close(){
			close(sock_fd);
		}
		//Getter
		inline int GetSockFd(){ return sock_fd; }
		//Setter
		inline void SetSockFd(int fd){ sock_fd = fd; }
	private:
		int sock_fd;
	};
};
#endif
