#ifndef __ONEPOKER_SERVER_PROTOCOL_HEADER__
#define __ONEPOKER_SERVER_PROTOCOL_HEADER__
#include "util/TripleSearchTree.hpp"
#include "util/Protocol.hpp"
#include <map>
using namespace std;
namespace CARDGAME{
	class Protocol{
	public:
		Protocol(){}
		~Protocol(){}
		
		/*
		 * 프로토콜 데이터를 초기화한다.
		 */
		static void InitProtocolData();
		
		/*
		 * method 를 검색한다.
		 */
		enum PROTOCOL_METHOD SearchMethod(string & method);
		
		enum PROTOCOL_TYPE SearchType(enum PROTOCOL_METHOD method, string & type);
		map<string, string> & GetData(string & proto_data);
		static void Clear();
	private:
		static TripleSearchTree method_tree;
		static TripleSearchTree type_tree;
		map<string, string> field_data;
	};
};

#endif
