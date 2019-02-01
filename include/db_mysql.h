#ifndef DB_MYSQL_H
#define DB_MYSQL_H
#include <string>
#include <mysql/mysql.h>

class DBMysql
{
public:
	DBMysql();
	~DBMysql();

	struct MysqlConnect
	{
		std::string url;
		int			port;
		std::string user_name;
		std::string user_pass;
		std::string use_db;
	};
 	bool OpenDB();

	void CloseDB();

	void SetConnect(MysqlConnect*connect);

	void GetConnect(MysqlConnect*connect);

    bool DoSqlQuery(const std::string& sql_query,const std::string& query_type,int task_id);

private:
	MYSQL mysql_;
	MysqlConnect* connect_;
};

extern DBMysql* g_db_mysql;
#endif
