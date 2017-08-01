#ifndef __ONEPOKER_SERVER_EPOLL_HEADER__
#define __ONEPOKER_SERVER_EPOLL_HEADER__
#include "util/ServerSocket.hpp"

#include <cstdlib>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace CARDGAME{
	class Epoll {
	public:
		Epoll():epoll_fd(0),
			max_client_count(0),
			ep_event(NULL){}

		Epoll(int client_count){
			Create(client_count);
		}

		~Epoll() {
			Close();
		}

		/*
		 * Epoll 디스크립터 생성
		 * @param
		 * client_count - epoll 디스크립터에서 저장할 수 있는 디스크립터의 수
		 * @return
		 * 성공시 - 0
		 * 실패시 - -1
		 */
		int Create(int client_count){
			epoll_fd = epoll_create(client_count);
			if(epoll_fd == -1)
				return -1;
			ep_event = (struct epoll_event *)malloc(sizeof(struct epoll_event) * client_count);
			if(ep_event == NULL)
				return -1;
			max_client_count = client_count;
			return 0;
		}
		
		/*
		 * epoll 디스크립터를 닫아주거나.
		 * epoll_event 구조체에 할당되어있는 메모리를 해제한다.
		 */
		void Close(){
			if(epoll_fd != 0)
				close(epoll_fd);
			if(ep_event != NULL)
				free(ep_event);
		}

		/*
		 * epoll 디스크립터에 fd 디스크립터를 추가한다.
		 * @param
		 * fd - 추가할 디스크립터.
		 * @return
		 * 성공시 - 0
		 * 디스크립터가 이미 최대치일 경우 - -1
		 * 디스크립터 추가에 실패했을 경우 - -2
		 */
		int AddFd(int fd){
			struct epoll_event ep_info;
			ep_info.data.fd = fd;
			ep_info.events = EPOLLIN;
			//이미 epoll 디스크립터에 최대 디스크립터가 지정되어 있을 경우
			if(max_client_count <= fd_list.size())
				return -1;
			if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ep_info) == -1)
				return -2;
			fd_list.push_back(fd);
			return 0;
		}
	
		/*
		 * Epoll 디스크립터에서 fd 디스크립터를 제거한다.
		 * @param
		 * fd - 제거할 디스크립터
		 * @return
		 * 성공시 - 0
		 * 실패시 - -1
		 */
		int DelFd(int fd){
			if(epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL) == -1)
				return -1;
			for(auto i = fd_list.begin(); i != fd_list.end(); ){
				if(*i == fd){
#ifdef ONEPOKER_DEBUG
					cout << "Delete in fd_list FD" << endl;
#endif
					i = fd_list.erase(i);
				} else
					i++;
			}
			return 0;
		}

		/*
		 * 저장된 디스크립터에서 이벤트가 발생하기를 기다린다.
		 * @param
		 * timeout - 타임아웃 시간을 지정한다. 인자가 없이 호출될경우 무한하게 기다린다,
		 * @return
		 * 동시에 일어난 이벤트의 개수를 반환한다.
		 */
		inline int WaitEvent(){
			return WaitEvent(-1);
		}
		
		inline int WaitEvent(int timeout){
			ep_event_index = 0;
			ep_event_count = epoll_wait(epoll_fd, ep_event, max_client_count, timeout);
			return ep_event_count;
		}

		/*
		 * 이벤트가 발생한 소켓 디스크립터를 반환한다.
		 * @return
		 * 성공시 - 소켓 디스크립터
		 * 더이상 없을 경우 - 0 을 반환
		 */
		int GetEventFd(){
			if(ep_event_index == ep_event_count)
				return 0;
			return ep_event[ep_event_index++].data.fd;
		}

		bool BroadCastMessage(string data, int serv_sock){
			bool check_success = true;
			for(auto sock_fd : fd_list){ 
				if(sock_fd == serv_sock) continue;
				else if(send(sock_fd, data.c_str(), data.length() + 1, 0) == -1)
					check_success = false;
			}
			return check_success;
		}
	private:
		int epoll_fd;
		vector<int> fd_list;
		unsigned int max_client_count;
		struct epoll_event * ep_event;
		int ep_event_count;
		int ep_event_index;
	};
};
#endif
