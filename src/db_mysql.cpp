#include "db_mysql.h"
#include "easylogging++.h"

DBMysql* g_db_mysql = new DBMysql();

DBMysql::DBMysql()
{
	connect_ = nullptr;
}

DBMysql::~DBMysql()
{
	delete connect_;
}


bool DBMysql::OpenDB()
{
	if (!connect_)
		return false;

	if (mysql_init(&mysql_) == NULL) {
		//std::cout << "初始化数据库失败" << std::endl;
		return false;
	}


	if (!mysql_real_connect(&mysql_, connect_->url.c_str(), connect_->user_name.c_str(),
							connect_->user_pass.c_str(),connect_->use_db.c_str(), 
							connect_->port, NULL, 0))
	{
		std::string error= mysql_error(&mysql_);
		LOG(ERROR) << "openDB : " << "数据库连接失败:"<<error;
		return false;
	}

	return true;
}

void DBMysql::SetConnect(MysqlConnect*connect)
{
	connect_ = connect;
}

void DBMysql::GetConnect(MysqlConnect*connect)
{
	connect = connect_;
}

bool DBMysql::DoSqlQuery(const std::string& sql_query,const std::string& query_type ,int task_id )
{
	
  int res = mysql_query(&mysql_, sql_query.c_str());
  if (res)
  {
  	LOG(ERROR) << "task id : " << task_id << "SQL FAIL:" << sql_query << "\n";
  	return false;
  }

  if (query_type == "1")
  {
	  MYSQL_RES *result = mysql_store_result(&mysql_);
	  size_t num_rows = mysql_num_rows(result);
	  for (size_t i = 0; i < num_rows; ++i) 
	  {
		  MYSQL_ROW row = mysql_fetch_row(result);
		  LOG(INFO) << "task id : " << task_id << "column[0]:"<<row[0] << "\n";
	  }   
	  mysql_free_result(result);
  }

  return true;
}

void DBMysql::CloseDB()
{
	mysql_close(&mysql_);
}
