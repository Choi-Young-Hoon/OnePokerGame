#ifndef __ONEPOKER_DB_DATABASE_HEADER__
#define __ONEPOKER_DB_DATABASE_HEADER__
#include <iostream>
#include <vector>
#include <string>
#include <mysql.h>
#include "util/ErrorFlag.hpp"

using namespace std;

namespace CARDGAME{
	class DataBase{
	public:
		DataBase():db_result(NULL){}
		~DataBase(){}
		
		/*
		 * DB 에 연결한다.
		 * @param
		 * ip - DB 서버 ip
		 * user - DB 계정
		 * pwd - DB 암호
		 * @return
		 * 성공시 - OP_ERROR_FLAG::DB_CONNECT_SUCCESS 반환
		 * 실패시 - OP_ERROR_FLAG::DB_CONNECT_ERROR 반환
		 */
		static enum OP_ERROR_FLAG Connect(string ip, string user, string pwd);	

		/*
		 * DB와의 연결을 종료한다.
		 */
		static void Close();
		
		/*
		 * 쿼리를 수행한다.
		 * @param
		 * query - 수행할 쿼리
		 * @return
		 * 성공시 - true
		 * 실패시 - false
		 */
		bool QueryRun(string & query);
		
		/*
		 * 쿼리를 수행한 후 결과를 받아온다.
		 * @TODO
		 * QueryRun() 을 수행하고 호출할 것.
		 * @return
		 * 성공시 - true
		 * 실패시 - false
		 */
		bool GetResult();
		
		/*
		 * 쿼리 수행 결과의 row 를 한줄씩 가져온다.
		 * @TODO
		 * *data 가 초기화됨.
		 * 반드시 GetResult() 함수를 호출한 후 사용할것.
		 * @param
		 * *data - row 의 각 필드의 데이터를 저장할 vector 컨테이너.
		 * field_count - 필드의 개수.
		 * @return
		 * 더 반환할 ROW가 남아있을 경우 true
		 * 더이상 반환할 row 가 없으면 false 를 반환한다.
		 */
		bool GetData(vector<string> * data, int field_count);


		/*
		 * 현재 받은 결과의 필드 개수를 반환한다.
		 * @TODO
		 * GetResult() 함수를 호출한 후 사용할 것.
		 * @return
		 * 현재 받아온 결과의 필드 개수를 반환한다.
		 */
		inline int GetFieldCount(){
			return mysql_num_fields(db_result);
		}
		
		/*
		 * db_query_run() 에서 INSERT, DELETE 와 같은 결과가 없는
		 * 쿼리에 대해서 영향을 받은 개수를 구한다. (SELECT x)
		 * @return
		 * 영향을 받은 ROW의 수를 반환한다.
		 */
		inline int CheckEffectRow(){
			return mysql_affected_rows(&db);
		}

		/*
		 * GetResult() 함수를 호출시 받은 버퍼를 해제한다.
		 * @alert
		 * 각 함수들은 실패시 내부에서 해당 함수를 호출하여 할당된
		 * 메모리를 해제.
		 */
		inline void FreeData(){
			mysql_free_result(db_result);
		}

		/*
		 * SELECT 쿼리에서 결과가 있는지 비교하기 위해 
		 * 임시로 만들어 사용중.
		 * @return
		 * SELECT 쿼리에 대한 결과가 한개 이상 있을경우 true
		 * SELECT 쿼리에 대한 결과가 없을 경우 false
		 */
		inline bool GetRow(){
			db_data = mysql_fetch_row(db_result);
			if(db_data == NULL)
				return false;
			return true;
		}
	private:
		static MYSQL db;
		MYSQL_RES * db_result;
		MYSQL_ROW db_data;
	};
};
#endif
