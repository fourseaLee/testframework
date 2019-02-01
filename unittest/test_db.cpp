#include "testingsetup.h"
#include "asset_curl.h"
#include "json.hpp"
#include <iostream>
#include <vector>
#include "common.h"
#include "easylogging++.h"
#include "checkqueue.h"
#include "sync.h"
#include "threadsafety.h"
#include "testconfig.h"
#include <utility>
#include <boost/thread/thread.hpp>
#include "db_mysql.h"
using json = nlohmann::json;

struct TaskDB
{
	bool operator () ()
	{

	    bool ret = g_db_mysql->DoSqlQuery(sql_query,query_type,task_id);

		return ret;

	}

	std::string sql_query ;
	int task_id;
	std::string query_type;
	void swap(TaskDB& check)
	{
		std::swap(sql_query,check.sql_query);
		std::swap(query_type,check.query_type);
		std::swap(task_id,check.task_id);

	}
};


BOOST_FIXTURE_TEST_SUITE(db_test,TestingSetup)

BOOST_AUTO_TEST_CASE(db_query)
{
	std::string db_setting_file_path = "../conf/db_setting.conf";
	std::string db_query_file_path = "../conf/db_query.conf";

	DBMysql::MysqlConnect* connect_db = new  DBMysql::MysqlConnect();

	readDBConnect(connect_db , db_setting_file_path);

	std::vector<std::string> vect_db_query;
	std::vector<std::string> vect_query_type;
	readDBQuery(vect_db_query,vect_query_type ,db_query_file_path);
	g_db_mysql->SetConnect(connect_db);
	BOOST_CHECK(g_db_mysql->OpenDB());

	int size_db_query = vect_db_query.size();

	for (int i = 0; i < size_db_query; i++)
	{
		g_db_mysql->DoSqlQuery(vect_db_query[i],vect_query_type[i],i);
	}
}

BOOST_AUTO_TEST_CASE(db_query_mutil)
{

	std::string db_setting_file_path = "../conf/db_setting.conf";
	std::string db_query_file_path = "../conf/db_query.conf";

	DBMysql::MysqlConnect* connect_db = new  DBMysql::MysqlConnect();

    readDBConnect(connect_db , db_setting_file_path);

	std::vector<std::string> vect_db_query;
	std::vector<std::string> vect_query_type;
    readDBQuery(vect_db_query,vect_query_type ,db_query_file_path);
	g_db_mysql->SetConnect(connect_db);

	BOOST_CHECK(g_db_mysql->OpenDB());

	int size_db_query = vect_db_query.size();

	boost::thread_group threadGroup;
	CCheckQueue<TaskDB> task_check_queue(128);
	CCheckQueueControl<TaskDB> control(&task_check_queue);

	for (int i=0; i<5; i++)
		threadGroup.create_thread(boost::bind(&CCheckQueue<TaskDB>::Thread, boost::ref(task_check_queue)));

	for(int i = 0; i < size_db_query; i++) 
	{
		std::vector<TaskDB> vChecks;
		TaskDB check;
		check.sql_query = vect_db_query.at(i);
		check.query_type = vect_query_type.at(i);
		check.task_id = i;
		vChecks.push_back(TaskDB());
		check.swap(vChecks.back());
		control.Add(vChecks);
	}
	control.Wait();
	threadGroup.interrupt_all();
	threadGroup.join_all();
}

BOOST_AUTO_TEST_SUITE_END()
