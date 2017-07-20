#include "util/TripleSearchTree.hpp"
#include <iostream>
#include <string>
#include <stack>
using namespace std;
using namespace ONEPOKER;


bool TripleSearchTree::insert(const char * data, int type){
	Node ** node = &root;
	bool endFlag = false;
#ifdef ONEPOKER_DEBUG
	cout << "TripleSearchTree Insert(" << data << ") : ";
#endif
	while(*data != '\0'){
		endFlag = (*(data + 1) == '\0') ? true : false;
		if( (*node) == NULL){
#ifdef ONEPOKER_DEBUG
			cout << *data << " ";
#endif
			*node = makeNode(*data, type, endFlag);
			nodeCount++;
		} else if(*data < (*node)->getData()){
			node = &((*node)->left);
		} else if(*data == (*node)->getData()){
			node = &((*node)->down);
			data++;
		} else {
			node = &((*node)->right);
		}
	}
	dataCount++;
#ifdef ONEPOKER_DEBUG
	cout << "Finish" << endl;
#endif
	return true;
}

int TripleSearchTree::search(const char * data){
	Node * node = root;
#ifdef ONEPOKER_DEBUG
	cout << "TripleSearchTree search(" << data << ") : ";
#endif
	while(*data != '\0'){
		if(node == NULL)
			break;
		else if(*data < node->getData()){
			node = node->left;
		} else if(*data == node->getData()){
#ifdef ONEPOKER_DEBUG
			cout << *data << " ";
#endif
			if( (*(data+1) == '\0') && node->checkEnd() ){
#ifdef ONEPOKER_DEBUG
				cout << endl;
#endif
				return node->getType();
			}
			node = node->down;
			data++;
		} else 
			node = node->right;
	}
#ifdef ONEPOKER_DEBUG
	cout << endl;
#endif
	return -1;
}

void TripleSearchTree::clear(){
	Node * node = root;
	Node * temp = NULL;
	stack<Node*> temp_node;
#ifdef ONEPOKER_DEBUG
	cout << "TripleSearchTree clear() : nodeCount temp_node.size()" << endl;
#endif
	while(nodeCount){
		temp = node;
		temp_node.push(node);

#ifdef ONEPOKER_DEBUG
		cout << node->getData() << " ";
#endif
		if(node->left != NULL){
			node = node->left;
			temp->left = NULL;
		} else if(node->down != NULL){
			node = node->down;
			temp->down = NULL;
		} else if(node->right != NULL){
			node = node->right;
			temp->right = NULL;
		} else {
#ifdef ONEPOKER_DEBUG
			cout << endl << "delete before: " << nodeCount << " "; 
			cout << temp_node.size() << "\tdelete node: ";
			cout << node->getData() << " ";
			cout << static_cast<void*>(node) << "\t"; 
#endif
			delete node;
			temp_node.pop();
			node = temp_node.top();
			temp_node.pop();
			nodeCount--;
#ifdef ONEPOKER_DEBUG
			cout << "delete after: " << nodeCount << " ";
			cout << temp_node.size() << endl;
#endif
			/*
			 * @TODO 
			 * 이상하게 마지막에 root 노드를 제거할때
			 * 위의 else if 구문에서 세그먼테이션 오류가나
			 * 잠시 하드코딩.
			 */
			if(nodeCount == 1){
				delete root;
				break;
			}
		}
	}
	root = NULL;
}
