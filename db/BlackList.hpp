#ifndef __ONEPOKER_DB_BLACKLIST_HEADER__
#define __ONEPOKER_DB_BLACKLIST_HEADER__

#include "db/DataBase.hpp"
#include "util/Time.hpp"
#include <iostream>
#include <string>
using namespace std;

namespace ONEPOKER{
	class BlackList : public DataBase {
	public:
		BlackList(){}
		virtual ~BlackList(){}

		/*
		 * IP 혹은 계정을 검색한다.
		 * @param
		 * info - ip 또는 계정.
		 * @return
		 * 검색시 존재할 경우 - true
		 * 없을 경우 - false
		 */
		bool Search(string info);

		/*
		 * 데이터를 삽입한다. 
		 * @param
		 * info - ip 또는 계정
		 * reason - 추가한 이유(?)
		 * @param
		 * 성공시 - true
		 * 실패시 - false 
		 */
		bool Insert(string info, string reason);

		/*
		 * ip 또는 계정을 제거한다.
		 * @param
		 * info - 제거할 ip 또는 계정
		 * @return
		 * 성공시 - true
		 * 실패시 - false
		 */
		bool Remove(string info);

		virtual string & SearchQuery(string & info) = 0;
		virtual string & InsertQuery(string & info, string & reason) = 0;
		virtual string & RemoveQuery(string & info) = 0;
	};

	// 싱글톤
	class BlackIP : public BlackList {
	public:
		virtual ~BlackIP(){
			if(instance)
				delete instance;
		}
		static inline BlackIP * GetInstance(){
			if(!instance)
				instance = new BlackIP();
			return instance;
		}
		/*
		 * 검색을 위한 쿼리를 반환한다.
		 * @param
		 * info - 검색할 IP
		 */
		virtual string & SearchQuery(string & info);
		
		/*
		 * 데이터를 삽입할 쿼리를 반환한다.
		 * @param
		 * info - 추가할 IP
		 * reason - 사유
		 */
		virtual string & InsertQuery(string & info, string & reason);
		
		/*
		 * 데이터를 제거할 쿼리를 반환한다.
		 * @param
		 * info - 제거할 ip 
		 */
		virtual string & RemoveQuery(string & info);
	private:
		BlackIP(){}
		static BlackIP * instance;
		string query;
	};


	class BlackUser : public BlackList {
	public:
		virtual ~BlackUser(){
			if(instance)
				delete instance;
		}
		static inline BlackUser * GetInstance(){
			if(!instance)
				instance = new BlackUser();
			return instance;
		}
		//// 위와 같음 여기서 info는 계정
		virtual string & SearchQuery(string & info);
		virtual string & InsertQuery(string & info, string & reason);
		virtual string & RemoveQuery(string & info);
	private:
		BlackUser(){}
		static BlackUser * instance;
		string query;
	};
};

#endif
