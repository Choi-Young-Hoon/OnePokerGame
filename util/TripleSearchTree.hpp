#ifndef __ONEPOKER_UTIL_TREEPLESEARCHTREE_HEADER__
#define __ONEPOKER_UTIL_TREEPLESEARCHTREE_HEADER__
#include <iostream>
#include <string>
using namespace std;

namespace ONEPOKER{
	class TripleSearchTree{
	public:
		TripleSearchTree(): root(NULL), dataCount(0), nodeCount(0){}
		~TripleSearchTree(){
			if(root != NULL)
				clear();
		}

		bool insert(const char * data, int type);
		int search(const char * data);
		void clear();
		inline void setNodeType(int type){ this->nodeType = type; }
		inline int getNodeType(){ return nodeType; }
	private:


		class Node{
		public:
			Node():type(0){
				right = left = down = NULL;
				endFlag = false;
			}
			~Node(){}
			inline void setNodeData(char data, int type, bool endFlag){
				this->data = data;
				this->type |= type;
				this->endFlag = endFlag;
			}
			inline char getData(){ return data; }
			inline int getType(){ return type; }
			inline bool checkEnd(){ return endFlag; }
			
			Node * right, * left, * down;
		private:
			char data;
			int type;
			bool endFlag;
		};
		Node * root;
		inline Node * makeNode(const char data, int type, bool endFlag){
			Node * node = new Node();
			node->setNodeData(data, type, endFlag);
			return node;
		}

		int nodeType;
		int dataCount;
		int nodeCount;
	};
};
#endif
