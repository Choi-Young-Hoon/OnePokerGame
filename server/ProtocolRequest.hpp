#ifndef __ONEPOKER_SERVER_PROTOCOLREQUEST_HEADER__
#define __ONEPOKER_SERVER_PROTOCOLREQUEST_HEADER__
#include "server/Protocol.hpp"
#include "util/Protocol.hpp"
#include <map>
#include <string>
using namespace std;
namespace CARDGAME{
	class ProtocolRequest : public Protocol {
	public:
		ProtocolRequest(){}
		~ProtocolRequest(){}

		bool parse(string data);
		bool GetMethodString(string & method, string & data);
		bool GetTypeString(string & type, string & data);

		inline enum PROTOCOL_METHOD GetMethod(){ return method; }
		inline enum PROTOCOL_TYPE GetType(){ return type; }
		inline map<string, string> & GetData(){ return data; }
	private:
		enum PROTOCOL_METHOD method;
		enum PROTOCOL_TYPE type;
		map<string, string> data;
	};
};
#endif
