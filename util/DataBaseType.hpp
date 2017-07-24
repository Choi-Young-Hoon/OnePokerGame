#ifndef __ONPOKER_UTIL_DATABASETYPE_HEADER__
#define __ONPOKER_UTIL_DATABASETYPE_HEADER__
namespace CARDGAME{

	//DB_DATA_TYPE의 지정 문자열.
	static const char * DB_DATA_ENUM[] = {"X", "O"};

	enum DB_DATA_TYPE{
		EMAIL_CERT_NO = 0, //이메일 인증 여부
		EMAIL_CERT_YES 
	};
	

	//User 테이블 필드
	enum USER_TB{
		USER_NUM = 0,
		USER_ID,
		USER_PWD,
		USER_EMAIL,
		USER_EMAIL_CERT,
		USER_RESENT_ACCESS_DATE,
		USER_MONEY,
		USER_WIN,
		USER_LOSE,
		USER_RATING
	};
	
	//Card 리스트 테이블 필드
	enum CARD_LIST_TB{
		CARD_NAME = 0,
	};
	
	//Rating 리스트 테이블 필드
	enum RATING_TB{
		RATING_NAME = 0,
		RATING_CONDITION
	};
};	
#endif
