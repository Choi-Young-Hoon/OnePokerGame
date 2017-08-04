#include "server/MatchingThread.hpp"
#include <unistd.h>

using namespace CARDGAME;

vector<LinkList<int, PokerUser>> MatchingThread::user_queue;

bool MatchingThread::Init(){
	match_cond = MatchSync::GetInstance();
	if(match_cond == NULL)
		return false;
	LinkList<int, PokerUser> item;
	for(int i = 0; i < GAME_MODE::GAME_MODE_COUNT; i++)
		user_queue.push_back(item);
	return true;
}

bool MatchingThread::AddQueue(enum GAME_MODE mode, int sock_fd, PokerUser & user){
	if(user_queue[mode].AddNode(sock_fd, user))
		return false;
	MatchSync::GetInstance()->signal();
	return true;
}

bool MatchingThread::DelQueue(enum GAME_MODE mode){
	return DelQueue(mode, 1);
}

bool MatchingThread::DelQueue(enum GAME_MODE mode, int count){
	for(int i = 0; i < count ; i++){
		if(!user_queue[mode].DelFrontNode())
			return false;
	}
	return true;
}

bool MatchingThread::StartGame(enum GAME_MODE mode, LinkList<int, PokerUser> user_list){
	return true;
}

enum GAME_MODE MatchingThread::CheckClientQueueCount(int need_client_count){
	for(int i = 0; i < GAME_MODE::GAME_MODE_COUNT; i++){
		if(user_queue[i].GetNodeCount() >= need_client_count)
			return static_cast<enum GAME_MODE>(i);
	}
	return GAME_MODE::GAME_MODE_COUNT;
}

void MatchingThread::Run(){
	enum GAME_MODE mode;
	LinkList<int, PokerUser> user_temp;
	while(true){
		while((mode = CheckClientQueueCount(2)) == GAME_MODE_COUNT){
			match_cond->wait();
			match_cond->unlock();
		}
		for(int i = 0; i < 2; i++){
			user_temp.AddNode(user_queue[mode].GetFirstData(),
					  user_queue[mode].GetSecondData());
			DelQueue(mode);
		}
		StartGame(mode, user_queue[mode]);
	}
}
