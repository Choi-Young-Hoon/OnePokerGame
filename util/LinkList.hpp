#ifndef __ONEPOKER_UTIL_LINKLIST_HEADER__
#define __ONEPOKER_UTIL_LINKLIST_HEADER__

namespace CARDGAME {
	template <typename TYPE1, typename TYPE2>
	class LinkList {
	public:
		LinkList() : root(NULL){}
		~LinkList(){}
		
		bool AddNode(TYPE1 val_1, TYPE2 val_2);
		bool DelNode();

		bool GetNode();
		bool PopNode();

		/*
		 * 노드가 비어있는지 조사한다.
		 * 비어있지 않을 경우 - true
		 * 비어있을 경우 - false
		 */
		bool CheckNode(){
			if(root == NULL)
				return false;
			return true;
		}

		TYPE1 GetFirstData();
		TYPE2 GetSecondData();
	private:
		class LinkNode{
		public:
			LinkNode() : next(NULL) {}
			~LinkNode() {}
			inline void SetVal_1(TYPE1 val){ val_1 = val; }
			inline void SetVal_2(TYPE2 val){ val_2 = val; }
			inline TYPE1 GetVal_1(){ return val_1; }
			inline TYPE2 GetVal_2(){ return val_2; }
		private:
			TYPE1 val_1;
			TYPE2 val_2;
			LinkNode * next;
		};
		LinkNode * root;
	};
};
#endif
