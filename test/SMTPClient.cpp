#include "util/SMTPClient.hpp"
using namespace CARDGAME;

int main(void){
	SmtpClient smtp;

	smtp.SetSubject("Hello title");
	smtp.SetSender("test@test.com");
	smtp.SetReceiver("hun5077@gmail.com");
	smtp.SetData("hello world!!!\nhahahahaha");

	if(!smtp.Connect())
		return -1;
	if(!smtp.Send())
		return -1;
	smtp.Close();
	return 0;
}
