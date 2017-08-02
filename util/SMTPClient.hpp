#ifndef __ONEPOKER_UTIL_SMTPCLIENT_HEADER__
#define __ONEPOKER_UTIL_SMTPCLIENT_HEADER__
#include <string>
using namespace std;

namespace CARDGAME {
	class SmtpClient{
	public:
		SmtpClient()
			:smtp_server_ip("127.0.0.1"), smtp_server_port(25){}
		SmtpClient(string & ip, int port)
			:smtp_server_ip(ip), smtp_server_port(port){}
		~SmtpClient(){}

		bool Connect();
		bool Send();
		bool Close();


		//Setter
		inline void SetServerAddress(string ip){ smtp_server_ip = ip; }
		inline void SetServerPort(int port){ smtp_server_port = port; }
		inline void SetSubject(string title){ subject = title; }
		inline void SetSender(string user){ sender = user; }
		inline void SetReceiver(string user){ receiver = user; }
		inline void SetData(string data){ this->data = data; } 
		//Getter
		inline string GetServerAddress(){ return smtp_server_ip; }
		inline int GetServerPort(){ return smtp_server_port; }
	private:
		int sock_fd;
		string smtp_server_ip;
		int smtp_server_port;
		
		string sender;
		string receiver;
		string subject;
		string data;
	};
};
#endif
