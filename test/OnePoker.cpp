#include "db/User.hpp"
#include "game/OnePoker.hpp"
#include "util/GameType.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace CARDGAME;
using namespace CARDGAME::ONEPOKER;

void ShowCard(vector<PokerCard> & card);
string WhatIsThisCard(enum CARD_TYPE type);
string WhatIsThisCard(enum CARD card);
string WhatIsThis(enum PLAYER player);

int main(void){
	if(DataBase::Connect("127.0.0.1", "root", "950214") 
			== OP_ERROR_FLAG::DB_CONNECT_ERROR)
		return -1;

	User user;
	UserData user1_data, user2_data;
	cout << "Get User : hun5077, eqw456" << endl;
	if(!user.Search("hun5077", "123123", &user1_data)){
		cout << "User Search Failed hun5077" << endl;
		return -1;
	}
	if(!user.Search("eqw456", "123123", &user2_data)){
		cout << "User Search Failed eqw456" << endl;
		return -1;
	}


	PokerUser user1, user2;
	user1.SetUserData(user1_data);
	user2.SetUserData(user2_data);


	CardDataMapInit();
	CardGame * poker_game = SelectGameMode(GAME_MODE::GAME_ONEPOKER);
	if(poker_game == NULL)
		return -1;
	if(!poker_game->SetUser(user1)){
		cout << "PokerGame SetUser Failed user1" << endl;
		return -1;
	}
	if(!poker_game->SetUser(user2)){
		cout << "PokerGame SetUser Failed user2" << endl;
		return -1;
	}
	
	PokerCard card;
	card.SetCard(CARD_DOWN, CARD_2, CARD_NON);
	poker_game->SetCard(PLAYER_1, card);
	card.SetCard(CARD_UP, CARD_A, CARD_NON);
	poker_game->SetCard(PLAYER_2, card);
	card.SetCard(CARD_UP, CARD_9, CARD_NON);
	poker_game->SetCard(PLAYER_1, card);
	card.SetCard(CARD_UP, CARD_8, CARD_NON);
	poker_game->SetCard(PLAYER_2, card);
	
	poker_game->SetOpenCard(PLAYER::PLAYER_1, CARD_INDEX::CARD_FIRST);
	poker_game->SetOpenCard(PLAYER::PLAYER_2, CARD_INDEX::CARD_FIRST);

	vector<PokerCard> show_card;
	cout << "Player 1 Open Card Info" << endl;
	show_card = poker_game->GetOpenCardList(PLAYER::PLAYER_1);
	ShowCard(show_card);
	
	cout << "Player 2 Open Card Info" << endl;
	show_card = poker_game->GetOpenCardList(PLAYER::PLAYER_2);
	ShowCard(show_card);


	switch(poker_game->CheckWinner()){
		case PLAYER::PLAYER_1:
			cout << "Player1 Win" << endl;
			break;
		case PLAYER::PLAYER_2:
			cout << "Player2 Win" << endl;
			break;
		case PLAYER::PLAYER_NON:
			cout << "DRAW!!!!!!" << endl;
			break;
	}
	poker_game->GameFinish();

	delete poker_game;
	DataBase::Close();
	return 0;
}

void ShowCard(vector<PokerCard> & card_list){
	for(auto & card : card_list){
		cout << "Card type : " << WhatIsThisCard((enum CARD_TYPE)card.GetType()) << endl;
		cout << "Card name : " << WhatIsThisCard(card.GetName()) << endl;
		cout << "Card win : " << WhatIsThisCard(card.GetWinCard()) << endl;
	}
}

string WhatIsThisCard(enum CARD_TYPE type){
	switch(type){
		case CARD_NON_TYPE: return "CARD_NON_TYPE";
		case CARD_DOWN: return "CARD_DOWN";
		case CARD_UP: return "CARD_UP";
	}
	return "";
}

string WhatIsThisCard(enum CARD card){
	switch(card){
		case CARD_NON: return "CARD_NON";
		case CARD_2: return "CARD_2";
		case CARD_3: return "CARD_3";
		case CARD_4: return "CARD_4";
		case CARD_5: return "CARD_5";
		case CARD_6: return "CARD_6";
		case CARD_7: return "CARD_7";
		case CARD_8: return "CARD_8";
		case CARD_9: return "CARD_9";
		case CARD_10: return "CARD_10";
		case CARD_K: return "CARD_K";
		case CARD_Q: return "CARD_Q";
		case CARD_J: return "CARD_J";
		case CARD_A: return "CARD_A";
	}
	return "";
}

string WhatIsThis(enum PLAYER player){
	switch(player){
		case PLAYER_1: return "PLAYER 1";
		case PLAYER_2: return "PLAYER_2";
		case PLAYER_NON: return "PLAYER_NON";
	}
	return "PLAYER_NON";
}
			     
