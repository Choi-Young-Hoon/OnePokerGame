#include "util/LinkList.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace CARDGAME;

int main(void){
	LinkList<int, string> list;

	//Insert DATA
	for(int i = 100, j = 200; i < 1000; i+=100, j+=100){
		if(!list.AddNode(i, to_string(j))){
			cout << "AddNode Error" << i << " " << j << endl;
			break;
		}
	}
	cout << "Node Count : " << list.GetNodeCount() << endl;
	for(int i = 0; i < 3; i++){
		if(list.CheckNode()){
			cout << i << "번쨰 : " << list.GetFirstData() 
				<< " " << list.GetSecondData() << endl;
		}
		if(!list.DelFrontNode()){
			cout << "DelFrontNode() Failed" << endl;
			break;
		}
	}
	list.Clear();
	return 0;
}
