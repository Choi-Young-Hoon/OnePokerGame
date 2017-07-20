#include "util/TripleSearchTree.hpp"
using namespace std;
using namespace ONEPOKER;

int main(void){
	TripleSearchTree data;

	data.insert("Hello",10); 
	data.insert("World", 20);
	data.insert("Good by", 30);
	data.insert("Godd", 40);
	cout << "search Hello : " << data.search("Hello") << endl;
	cout << "search Good : " << data.search("Good") << endl;
	cout << "search Good by : " << data.search("Good by") << endl;
	cout << "search World : " << data.search("World") << endl;
	cout << "search None : " << data.search("None") << endl;

	data.clear();
	return 0;
}
