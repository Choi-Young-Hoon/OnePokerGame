#ifndef __ONEPOKER_SERVER_PROTOCOLRESPONSE_HEADER__
#define __ONEPOKER_SERVER_PROTOCOLRESPONSE_HEADER__
#include "server/Protocol.hpp"
#include "util/Protocol.hpp"
#include "db/User.hpp"
#include <string>
#include <map>
using namespace std;

namespace CARDGAME{
	class ProtocolResponse : public Protocol {
	public:
		ProtocolResponse(){}
		~ProtocolResponse(){}

/*		string GetResponseData(enum PROTOCOL_METHOD method,
				       enum PROTOCOL_TYPE type,
				       map<string, string> & data,
				       UserData * user_info);
*/	private:
	};
};
#endif
