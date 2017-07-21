#include "util/GameType.hpp"
#include <map>
using namespace std;
using namespace ONEPOKER;

extern "C" int GetCardData(string data){
	return card_data[data];
}

extern "C" void CardDataMapInit(){
	card_data.insert(make_pair("d", CARD_TYPE::CARD_DOWN));
	card_data.insert(make_pair("u", CARD_TYPE::CARD_UP));

	card_data.insert(make_pair("2", CARD::CARD_2));
	card_data.insert(make_pair("3", CARD::CARD_3));
	card_data.insert(make_pair("4", CARD::CARD_4));
	card_data.insert(make_pair("5", CARD::CARD_5));
	card_data.insert(make_pair("6", CARD::CARD_6));
	card_data.insert(make_pair("7", CARD::CARD_7));
	card_data.insert(make_pair("8", CARD::CARD_8));
	card_data.insert(make_pair("9", CARD::CARD_9));
	card_data.insert(make_pair("10", CARD::CARD_10));
	card_data.insert(make_pair("K", CARD::CARD_K));
	card_data.insert(make_pair("Q", CARD::CARD_Q));
	card_data.insert(make_pair("J", CARD::CARD_J));
	card_data.insert(make_pair("A", CARD::CARD_A));
}
