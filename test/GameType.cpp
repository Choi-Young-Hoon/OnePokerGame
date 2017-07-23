#include <iostream>
#include "util/GameType.hpp"

using namespace std;
using namespace CARDGAME;

int main(void){
	CardDataMapInit();
	cout << "\"2\" : " << GetCardData("2") << endl;
	cout << "\"d\" : " << GetCardData("d") << endl;
	cout << "\"W\" : " << GetCardData("W") << endl;
	return 0;
}
