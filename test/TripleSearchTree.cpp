#include "util/TripleSearchTree.hpp"
using namespace std;
using namespace CARDGAME;

int main(void){
	TripleSearchTree data;

	data.Insert("Hello",10); 
	data.Insert("World", 20);
	data.Insert("Good by", 30);
	data.Insert("Godd", 40);
	cout << "search Hello : " << data.Search("Hello") << endl;
	cout << "search Good : " << data.Search("Good") << endl;
	cout << "search Good by : " << data.Search("Good by") << endl;
	cout << "search World : " << data.Search("World") << endl;
	cout << "search None : " << data.Search("None") << endl;

	data.Clear();
	return 0;
}
