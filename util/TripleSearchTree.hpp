#ifndef __ONEPOKER_UTIL_TREEPLESEARCHTREE_HEADER__
#define __ONEPOKER_UTIL_TREEPLESEARCHTREE_HEADER__
#include <iostream>
#include <string>
using namespace std;

namespace ONEPOKER{
	class TripleSearchTree{
	public:
		TripleSearchTree(): root(NULL), data_count(0), node_count(0){}
		~TripleSearchTree(){
			if(root != NULL)
				Clear();
		}

		bool Insert(const char * data, int type);
		int Search(const char * data);
		void Clear();
		inline void SetNodeType(int type){ this->node_type = type; }
		inline int GetNodeType(){ return node_type; }
	private:


		class Node{
		public:
			Node():type(0){
				right = left = down = NULL;
				end_flag = false;
			}
			~Node(){}
			inline void SetNodeData(char data, int type, bool end_flag){
				this->data = data;
				this->type |= type;
				this->end_flag = end_flag;
			}
			inline char GetData(){ return data; }
			inline int GetType(){ return type; }
			inline bool CheckEnd(){ return end_flag; }
			
			Node * right, * left, * down;
		private:
			char data;
			int type;
			bool end_flag;
		};
		Node * root;
		inline Node * MakeNode(const char data, int type, bool end_flag){
			Node * node = new Node();
			node->SetNodeData(data, type, end_flag);
			return node;
		}

		int node_type;
		int data_count;
		int node_count;
	};
};
#endif
