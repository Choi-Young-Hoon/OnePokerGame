#ifndef __ONEPOKER_UTIL_ERROR_HEADDER__
#define __ONEPOKER_UTIL_ERROR_HEADDER__

namespace ONEPOKER{
	enum OP_ERROR_FLAG{
		DB_CONNECT_SUCCESS = 0, //DB 연결 성공
		DB_CONNECT_ERROR, 	//DB 연결 실패
		DB_QUERY_ERROR,		//쿼리문이 잘못됨.
		DB_NON_RESULT		//쿼리 결과가 없음
	};	
};
#endif
