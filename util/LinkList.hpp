#ifndef __ONEPOKER_UTIL_LINKLIST_HEADER__
#define __ONEPOKER_UTIL_LINKLIST_HEADER__
#include <iostream>
using namespace std;
namespace CARDGAME {
	template <typename TYPE1, typename TYPE2>
	class LinkList {
	public:
		LinkList() : start_node(NULL), end_node(NULL), node_count(0) {}
		~LinkList(){
			Clear();
		}
		
		/*
		 * 노드 추가
		 * @param
		 * val_1 - 값 1
		 * val_2 - 값 2
		 * @return
		 * 성공시 - true
		 * 실패시 - flase
		 */
		bool AddNode(TYPE1 val_1, TYPE2 val_2){
			if(start_node == NULL){
				start_node = new LinkNode(val_1, val_2);
				if(start_node == NULL) return false;
				end_node = start_node;
			} else {
				end_node->next = new LinkNode(val_1, val_2);
				if(end_node->next == NULL) return false; 
				end_node = end_node->next;
			}
			node_count++;
			return true;
		}	
		
		/*
		 * 맨 앞 노드를 제거한다.
		 * @return 
		 * 제거 성공시 - true
		 * 더이상 제거할 노드가 없을 경우 - false
		 */
		bool DelFrontNode(){
			if(start_node == NULL)
				return false;
			LinkNode * temp = start_node->next;
			delete start_node;
			if(temp == NULL)
				start_node = end_node = temp;
			else
				start_node = temp;
			node_count--;
			return true;
		}

		/*
		 * 노드를 초기화한다.
		 */
		inline void Clear(){ while(DelFrontNode()){} }
		
		/*
		 * 노드가 비어있는지 조사한다.
		 * 비어있지 않을 경우 - true
		 * 비어있을 경우 - false
		 */
		bool CheckNode(){
			if(start_node == NULL)
				return false;
			return true;
		}

		//Getter
		inline TYPE1 GetFirstData(){ return start_node->GetVal_1(); }
		inline TYPE2 GetSecondData(){ return start_node->GetVal_2(); }
		inline int GetNodeCount(){ return node_count; }
	private:
		class LinkNode{
		public:
			LinkNode() : next(NULL) {}
			LinkNode(TYPE1 val_1, TYPE2 val_2){
				this->val_1 = val_1;
				this->val_2 = val_2;
				next = NULL;
			}
			~LinkNode() {}
			inline void SetVal_1(TYPE1 val){ val_1 = val; }
			inline void SetVal_2(TYPE2 val){ val_2 = val; }
			inline TYPE1 GetVal_1(){ return val_1; }
			inline TYPE2 GetVal_2(){ return val_2; }
			
			LinkNode * next;
		private:
			TYPE1 val_1;
			TYPE2 val_2;
		};
		LinkNode * start_node, * end_node;
		int node_count;
	};
};
#endif
