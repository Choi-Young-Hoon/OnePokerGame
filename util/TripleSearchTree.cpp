#include "util/TripleSearchTree.hpp"
#include <iostream>
#include <string>
#include <stack>
using namespace std;
using namespace CARDGAME;


bool TripleSearchTree::Insert(const char * data, int type){
	Node ** node = &root;
	bool end_flag = false;
#ifdef ONEPOKER_DEBUG
	cout << "TripleSearchTree Insert(" << data << ") : ";
#endif
	while(*data != '\0'){
		end_flag = (*(data + 1) == '\0') ? true : false;
		if( (*node) == NULL){
#ifdef ONEPOKER_DEBUG
			cout << *data << " ";
#endif
			*node = MakeNode(*data, type, end_flag);
			node_count++;
		} else if(*data < (*node)->GetData()){
			node = &((*node)->left);
		} else if(*data == (*node)->GetData()){
			node = &((*node)->down);
			data++;
		} else {
			node = &((*node)->right);
		}
	}
	data_count++;
#ifdef ONEPOKER_DEBUG
	cout << "Finish" << endl;
#endif
	return true;
}

int TripleSearchTree::Search(const char * data){
	Node * node = root;
#ifdef ONEPOKER_DEBUG
	cout << "TripleSearchTree search(" << data << ") : ";
#endif
	while(*data != '\0'){
		if(node == NULL)
			break;
		else if(*data < node->GetData()){
			node = node->left;
		} else if(*data == node->GetData()){
#ifdef ONEPOKER_DEBUG
			cout << *data << " ";
#endif
			if( (*(data+1) == '\0') && node->CheckEnd() ){
#ifdef ONEPOKER_DEBUG
				cout << endl;
#endif
				return node->GetType();
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

void TripleSearchTree::Clear(){
	Node * node = root;
	Node * temp = NULL;
	stack<Node*> temp_node;
#ifdef ONEPOKER_DEBUG
	cout << "TripleSearchTree clear() : nodeCount temp_node.size()" << endl;
#endif
	while(node_count){
		temp = node;
		temp_node.push(node);

#ifdef ONEPOKER_DEBUG
		cout << node->GetData() << " ";
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
			cout << endl << "delete before: " << node_count << " "; 
			cout << temp_node.size() << "\tdelete node: ";
			cout << node->GetData() << " ";
			cout << static_cast<void*>(node) << "\t"; 
#endif
			delete node;
			temp_node.pop();
			node = temp_node.top();
			temp_node.pop();
			node_count--;
#ifdef ONEPOKER_DEBUG
			cout << "delete after: " << node_count << " ";
			cout << temp_node.size() << endl;
#endif
			/*
			 * @TODO 
			 * 이상하게 마지막에 root 노드를 제거할때
			 * 위의 else if 구문에서 세그먼테이션 오류가나
			 * 잠시 하드코딩.
			 */
			if(node_count == 1){
				delete root;
				break;
			}
		}
	}
	root = NULL;
}
