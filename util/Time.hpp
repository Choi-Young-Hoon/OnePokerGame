#ifndef __ONEPOKER_UTIL_TIME_HEADER__
#define __ONEPOKER_UTIL_TIME_HEADER__
#include <iostream>
#include <string>
using namespace std;
#include <time.h>

namespace CARDGAME{
	
	/*
	 * 현재 날짜 반환 함수 형식 yyyy-mm-dd
	 */
	inline string GetTimeyyyymmdd(){
		char buf[40] = {0,};
		time_t sec_time;
		struct tm * tm;

		sec_time = time(NULL);
		tm = localtime(&sec_time);

		sprintf(buf, "%d-%d-%d", tm->tm_year + 1900
				, tm->tm_mon + 1, tm->tm_mday);
		return buf;
	}
};

#endif
