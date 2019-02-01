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
using json = nlohmann::json;

struct TaskConcurrent
{
	bool operator () ()
	{

		std::string code_response;
		CurlPost(url_bron, post_code_data, code_response);
		if (code_response.empty()) 
		{
			std::cout << "code failed" << std::endl;
			return false;
		}
		json bron_response = json::parse(code_response);
		std::string data = bron_response["data"].get<std::string>();
		json json_entrust;                                                                                                                   
		json_entrust["apiKey"] = apiKey;                          
		json_entrust["data"] = data;    
		std::string tran_response;                                                                 
		CurlPost(url_entrust, json_entrust.dump(), tran_response);
		if (tran_response.empty())
		{
			std::cout << "tran  failed" << std::endl;
			return false;
		}
		json tran_json = json::parse(tran_response);
		int code = tran_json["code"].get<int>(); 
		if (code == 200)
		{
			std::cout << "task : " << task_id << "success :" << tran_response << std::endl;
		}
		return true;

	}

	TaskConcurrent()
	{
		std::string url_file_path  = "../conf/url.conf";
		readUrlFromJsonConf( url_bron,url_entrust ,url_file_path);
	}

	int task_id;
	std::string url_bron; 
	std::string url_entrust ;
	std::string post_code_data;
	std::string apiKey;

	void swap(TaskConcurrent& check)
	{
		std::swap(post_code_data,check.post_code_data);
		std::swap(apiKey,check.apiKey);
    	std::swap(task_id,check.task_id);
	}
};


BOOST_FIXTURE_TEST_SUITE(concurrent_test,TestingSetup)

BOOST_AUTO_TEST_CASE(mutil_single_test)
{
	std::string user_file_path = "../conf/mutil_user.conf" ;
	std::string entrust_file_path = "../conf/single_mutil_entrust.conf" ;
	std::vector<UserInfo*> users;
	std::vector<EntrustInfo*> entrusts;
	decodeUserConfig(users,user_file_path);
	decodeEntrustConfig(entrusts,entrust_file_path);

	int size_entrusts = entrusts.size();

	boost::thread_group threadGroup;
	CCheckQueue<TaskConcurrent> task_check_queue(128);
	CCheckQueueControl<TaskConcurrent> control(&task_check_queue);

	for (int i=0; i<5; i++)
		threadGroup.create_thread(boost::bind(&CCheckQueue<TaskConcurrent>::Thread, boost::ref(task_check_queue)));

	for(int i = 0; i < 5000; i++) 
	{
		std::vector<TaskConcurrent> vChecks;
		TaskConcurrent check;
		int uidx = i % users.size();
		int eidx = i % size_entrusts;
		json post_data;
		post_data["Fpublickey"] = users[uidx]->pubKey;
		post_data["secretKey"] = users[uidx]->secretKey;                                                      
		post_data["pairname"] = entrusts[eidx]->pairname;                                                           
		post_data["type"] = entrusts[eidx]->type;
		post_data["price"] = entrusts[eidx]->price;                                                                      
		post_data["count"] = entrusts[eidx]->count;
		post_data["amount"] = entrusts[eidx]->amount;
		post_data["entrustIdList"] = "";                                                                     
		post_data["currentPage"] = "1";

		check.post_code_data = post_data.dump();
		check.apiKey = users[uidx]->apiKey;
		check.task_id = i;
		vChecks.push_back( TaskConcurrent());
		//	vChecks.push_back(TaskCheck(i+1,i*i));
		check.swap(vChecks.back());
		control.Add(vChecks);
	}
	control.Wait();
	threadGroup.interrupt_all();
	threadGroup.join_all();
}



BOOST_AUTO_TEST_CASE(mutil_thread_queue)
{
	std::string user_file_path = "../conf/user.conf" ;
	std::string entrust_file_path = "../conf/entrust.conf" ;
	std::vector<UserInfo*> users;
	std::vector<EntrustInfo*> entrusts;
	decodeUserConfig(users,user_file_path);
	decodeEntrustConfig(entrusts,entrust_file_path);

	int size_entrusts = entrusts.size();

	boost::thread_group threadGroup;
	CCheckQueue<TaskConcurrent> task_check_queue(128);
	CCheckQueueControl<TaskConcurrent> control(&task_check_queue);

	for (int i=0; i<5; i++)
		threadGroup.create_thread(boost::bind(&CCheckQueue<TaskConcurrent>::Thread, boost::ref(task_check_queue)));

	for(int i = 0; i < size_entrusts; i++) 
	{
		std::vector<TaskConcurrent> vChecks;
		TaskConcurrent check;
		int uidx = rand() % users.size();
		json post_data;
		post_data["Fpublickey"] = users[uidx]->pubKey;
		post_data["secretKey"] = users[uidx]->secretKey;                                                      
		post_data["pairname"] = entrusts[i]->pairname;                                                           
		post_data["type"] = entrusts[i]->type;
		post_data["price"] = entrusts[i]->price;                                                                      
		post_data["count"] = entrusts[i]->count;
		post_data["amount"] = entrusts[i]->amount;
		post_data["entrustIdList"] = "";                                                                     
		post_data["currentPage"] = "1";
	
		check.post_code_data = post_data.dump();
		check.apiKey = users[uidx]->apiKey;
		vChecks.push_back( TaskConcurrent());
		//	vChecks.push_back(TaskCheck(i+1,i*i));
		check.swap(vChecks.back());
		control.Add(vChecks);
	}
	control.Wait();
	threadGroup.interrupt_all();
	threadGroup.join_all();
}


BOOST_AUTO_TEST_CASE(lowbuy_highsell)
{
	std::string user_file_path = "../conf/user.conf" ;
	std::string lowbuy_file_path = "../conf/lowpricebuy.conf" ;
	std::string highsell_file_path = "../conf/histpricesell.conf";
	std::vector<UserInfo*> users;
	std::vector<EntrustInfo*> lowbuy_entrusts;
	std::vector<EntrustInfo*> highsell_entrusts;
	decodeUserConfig(users,user_file_path);
	decodeEntrustConfig(lowbuy_entrusts,lowbuy_file_path);
	decodeEntrustConfig(highsell_entrusts,highsell_file_path);

	int size_lowbuy = lowbuy_entrusts.size();
	int size_highsell = highsell_entrusts.size();


	boost::thread_group threadGroup;
	CCheckQueue<TaskConcurrent> task_check_queue(128);
	CCheckQueueControl<TaskConcurrent> control(&task_check_queue);

	for (int i=0; i<5; i++)
		threadGroup.create_thread(boost::bind(&CCheckQueue<TaskConcurrent>::Thread, boost::ref(task_check_queue)));

	for(int i = 0; i < size_lowbuy; i++) 
	{
		std::vector<TaskConcurrent> vChecks;
		TaskConcurrent check;
		int uidx = rand() % users.size();
		json post_data;
		post_data["Fpublickey"] = users[uidx]->pubKey;
		post_data["secretKey"] = users[uidx]->secretKey;                                                      
		post_data["pairname"] = lowbuy_entrusts[i]->pairname;                                                           
		post_data["type"] = lowbuy_entrusts[i]->type;
		post_data["price"] = lowbuy_entrusts[i]->price;                                                                      
		post_data["count"] = lowbuy_entrusts[i]->count;
		post_data["amount"] = lowbuy_entrusts[i]->amount;
		post_data["entrustIdList"] = "";                                                                     
		post_data["currentPage"] = "1";
	
		check.post_code_data = post_data.dump();
		check.apiKey = users[uidx]->apiKey;
		vChecks.push_back( TaskConcurrent());
		//	vChecks.push_back(TaskCheck(i+1,i*i));
		check.swap(vChecks.back());
		control.Add(vChecks);
	}

	for(int i = 0; i < size_highsell; i++) 
	{
		std::vector<TaskConcurrent> vChecks;
		TaskConcurrent check;
		int uidx = rand() % users.size();
		json post_data;
		post_data["Fpublickey"] = users[uidx]->pubKey;
		post_data["secretKey"] = users[uidx]->secretKey;                                                      
		post_data["pairname"] = highsell_entrusts[i]->pairname;                                                           
		post_data["type"] = highsell_entrusts[i]->type;
		post_data["price"] = highsell_entrusts[i]->price;                                                                      
		post_data["count"] = highsell_entrusts[i]->count;
		post_data["amount"] = highsell_entrusts[i]->amount;
		post_data["entrustIdList"] = "";                                                                     
		post_data["currentPage"] = "1";
	
		check.post_code_data = post_data.dump();
		check.apiKey = users[uidx]->apiKey;
		vChecks.push_back( TaskConcurrent());
		//	vChecks.push_back(TaskCheck(i+1,i*i));
		check.swap(vChecks.back());
		control.Add(vChecks);
	}


	control.Wait();
	threadGroup.interrupt_all();
	threadGroup.join_all();
}

BOOST_AUTO_TEST_SUITE_END()
