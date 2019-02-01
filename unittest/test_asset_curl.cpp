#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "testingsetup.h"
#include "asset_curl.h"
#include "common.h"
#include "json.hpp"
#include "testconfig.h"

using json = nlohmann::json;


std::string url_bron = "http://192.168.0.19:8080/app/v1/bronJsonVen";
std::string url_entrust = "http://192.168.0.19:8080/app/v1/entrustSubmitCus";
BOOST_FIXTURE_TEST_SUITE(asset_curl_test, TestingSetup)

BOOST_AUTO_TEST_CASE(singleUser)
{
	std::vector<UserInfo*> users;
	std::string user_file_path = "../conf/single_user.conf" ;
	

	decodeUserConfig(users,user_file_path);
	for (auto &ele: users)
		std::cout << ele->apiKey << ", " << ele->secretKey << ", " << ele->pubKey << std::endl;


	std::string entrust_file_path = "../conf/single_entrust.conf" ;
	std::vector<EntrustInfo*> entrusts;
	decodeEntrustConfig(entrusts,entrust_file_path);
 	int count_entrust = 0;
	std::string url_file_path  = "../conf/url.conf";
    readUrlFromJsonConf( url_bron,url_entrust ,url_file_path);
	for (int i = 0; i<500 ; ++i)
	{
 		int uidx = rand() % users.size();
		int eidx = i% entrusts.size();
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
	
		std::cout << "price: " << entrusts[eidx]->price << std::endl; 
		//std::cout << "out put url_bron: " << url_bron <<  std::endl;
		std::string response;
		//std::cout << "url_bron post:" << post_data.dump() << std::endl;
		CurlPost(url_bron, post_data.dump(), response);
		if (response.empty()) 
		{
			std::cout << "bronJsonVen failed" << std::endl;
			return;
		}

//		std::cout << "bron response: " << response << std::endl;

		json bron_response = json::parse(response);
		std::string data = bron_response["data"].get<std::string>();
		json json_entrust;                                                                                                                   
		json_entrust["apiKey"] = users[uidx]->apiKey;                          
		json_entrust["data"] = data;    
		response.clear();                                          
		
		//std::cout << "out put url_entrust: " << url_entrust << std::endl;
		CurlPost(url_entrust, json_entrust.dump(), response);

		json show_json = json::parse(response);

		int code =  show_json["code"].get<int>();
		if ( code == 200 )
		{
			count_entrust ++;
		}
		std::cout << response << std::endl;
		/*
		if (0 == eidx%2)
		{
			sleep(1);
			}*/
	}

	std::cout <<  std::endl << std::endl << std::endl;

	std::cout << "succuss  cout:" << count_entrust << std::endl; 

/*	for (auto &ele: entrusts)
	{
		std::cout << ele->pairname << ", " << ele->type << ", " << ele->price;
		std::cout << ", " << ele->count << ", " << ele->amount << std::endl;
	}*/
}
BOOST_AUTO_TEST_CASE(TaiwanTest)
{
	std::vector<UserInfo*> users;
	std::string user_file_path = "../conf/user_taiwan.conf" ;
	

	decodeUserConfig(users,user_file_path);
	for (auto &ele: users)
		std::cout << ele->apiKey << ", " << ele->secretKey << ", " << ele->pubKey << std::endl;


	std::string entrust_file_path = "../conf/taiwan_entrust.conf" ;
	std::vector<EntrustInfo*> entrusts;
	decodeEntrustConfig(entrusts,entrust_file_path);
 	int count_entrust = 0;
	std::string url_file_path  = "../conf/url_taiwan.conf";
    readUrlFromJsonConf( url_bron,url_entrust ,url_file_path);
	for (int i = 0; i  < 1; ++i)
	{
 		int uidx = 0;//rand() % users.size();
		int eidx = i% entrusts.size();
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
	
		
		std::string response;
		CurlPost(url_bron, post_data.dump(), response);
		if (response.empty()) 
		{
			std::cout << "bronJsonVen failed" << std::endl;
			return;
		}


		json bron_response = json::parse(response);
		std::string data = bron_response["data"].get<std::string>();
		json json_entrust;                                                                                                                   
		json_entrust["apiKey"] = users[uidx]->apiKey;                          
		json_entrust["data"] = data;    
		response.clear();                                          
		
		CurlPost(url_entrust, json_entrust.dump(), response);

		json show_json = json::parse(response);

		int code =  show_json["code"].get<int>();
		if ( code == 200 )
		{
			count_entrust ++;
		}
		std::cout << response << std::endl;

     }

	std::cout <<  std::endl << std::endl << std::endl;

	std::cout << "succuss  cout:" << count_entrust << std::endl; 
}


BOOST_AUTO_TEST_CASE(entrustTest)
{
	std::vector<UserInfo*> users;
	std::vector<EntrustInfo*> entrusts;

	std::string user_file_path = "../conf/user.conf" ;

	std::string entrust_file_path = "../conf/entrust.conf" ;
	decodeUserConfig(users,user_file_path);
	decodeEntrustConfig(entrusts,entrust_file_path);
	std::string url_file_path  = "../conf/url.conf";
    readUrlFromJsonConf( url_bron,url_entrust ,url_file_path);
	for (int eidx = 0; eidx < entrusts.size(); ++eidx)
	{
 		int uidx = rand() % users.size();
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
	
		
		std::cout << "out put url_bron: " << url_bron <<  std::endl;
		std::string response;
		CurlPost(url_bron, post_data.dump(), response);
		if (response.empty()) 
		{
			std::cout << "bronJsonVen failed" << std::endl;
			return;
		}


		json bron_response = json::parse(response);
		std::string data = bron_response["data"].get<std::string>();
		json json_entrust;                                                                                                                   
		json_entrust["apiKey"] = users[uidx]->apiKey;                          
		json_entrust["data"] = data;    
		response.clear();                                          
		
		std::cout << "out put url_entrust: " << url_entrust << std::endl;
		CurlPost(url_entrust, json_entrust.dump(), response);
		std::cout << response << std::endl;

	}

	for (int i = 0; i < users.size(); i++)
		delete users[i];
	for (int i = 0; i < entrusts.size(); i++)
		delete entrusts[i];
	users.clear();
	entrusts.clear();
}


BOOST_AUTO_TEST_CASE(confTest31)
{

	std::string user_file_path = "../conf/user.conf" ;

	std::string entrust_file_path = "../conf/entrust.conf" ;
	std::vector<CodePostInfo*> vect_code;
	readJsonToCodeInfo(vect_code,user_file_path);
	std::string url_file_path  = "../conf/url.conf";
    readUrlFromJsonConf( url_bron,url_entrust ,url_file_path);
	for (int k = 0; k < 400; k++)
	{
		int i = k % 20;
		json  json_code_post_data ;
		json_code_post_data["Fpublickey"] = vect_code[i]->Fpublickey;
		json_code_post_data["secretKey"] = vect_code[i]->secretKey;
		json_code_post_data["type"] = std::to_string(rand()%2);
		json_code_post_data["pairname"] = "TEST3TEST1";
		json_code_post_data["price"] = std::to_string(rand()%10 + 20);
		json_code_post_data["count"] = std::to_string(rand()%1000 +100);
		json_code_post_data["amount"] = std::to_string(rand()%10000+1);
		json_code_post_data["entrustIdList"] = "";
		json_code_post_data["currentPage"] = "1";
		std::string code_post_data = json_code_post_data.dump();

		std::string code_post_response;
		CurlPost(url_bron, code_post_data, code_post_response);

		if (code_post_response == "" || code_post_response.empty())
			std::cout << "no data return !" << std::endl;

		json json_code_response = json::parse(code_post_response);
		std::string  data_post = json_code_response["data"].get<std::string>();
		json json_tran_post_data ;

		json_tran_post_data["apiKey"] = vect_code[i]->apiKey;
		json_tran_post_data["data"] = data_post;

		std::string tran_post_data = json_tran_post_data.dump();
		std::string tran_response_data;
		CurlPost(url_entrust, tran_post_data, tran_response_data);
		std::cout << tran_response_data << std::endl;
	}

	for (int i = 0; i < vect_code.size(); i++)
	{
		delete vect_code[i];
	}
	vect_code.clear();
}

BOOST_AUTO_TEST_CASE(lowrpricebuyTest)
{
	std::vector<UserInfo*> users;
	std::vector<EntrustInfo*> entrusts;

	std::string user_file_path = "../conf/user.conf" ;

	std::string entrust_file_path = "../conf/lowpricebuy.conf" ;
	decodeUserConfig(users,user_file_path);
	decodeEntrustConfig(entrusts,entrust_file_path);
	std::string url_file_path  = "../conf/url.conf";
    readUrlFromJsonConf( url_bron,url_entrust ,url_file_path);
	for (int eidx = 0; eidx < entrusts.size(); ++eidx)
	{
 		int uidx = rand() % users.size();
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
		
		std::string response;
		CurlPost(url_bron, post_data.dump(), response);
		if (response.empty()) 
		{
			std::cout << "bronJsonVen failed" << std::endl;
			return;
		}

		json bron_response = json::parse(response);
		std::string data = bron_response["data"].get<std::string>();
		json json_entrust;                                                                                                                   
		json_entrust["apiKey"] = users[uidx]->apiKey;                          
		json_entrust["data"] = data;    
		response.clear();                                                                  
		CurlPost(url_entrust, json_entrust.dump(), response);
		std::cout << response << std::endl;
	}

	for (int i = 0; i < users.size(); i++)
		delete users[i];
	for (int i = 0; i < entrusts.size(); i++)
		delete entrusts[i];
	users.clear();
	entrusts.clear();
}

BOOST_AUTO_TEST_CASE(highPriceSellTest)
{
	std::vector<UserInfo*> users;
	std::vector<EntrustInfo*> entrusts;

	std::string user_file_path = "../conf/user.conf" ;

	std::string entrust_file_path = "../conf/highpricesell.conf" ;
	decodeUserConfig(users,user_file_path);
	decodeEntrustConfig(entrusts,entrust_file_path);
	std::string url_file_path  = "../conf/url.conf";
    readUrlFromJsonConf( url_bron,url_entrust ,url_file_path);
	for (int eidx = 0; eidx < entrusts.size(); ++eidx)
	{
 		int uidx = rand() % users.size();
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
		
		std::string response;
		CurlPost(url_bron, post_data.dump(), response);
		if (response.empty()) 
		{
			std::cout << "bronJsonVen failed" << std::endl;
			return;
		}

		json bron_response = json::parse(response);
		std::string data = bron_response["data"].get<std::string>();
		json json_entrust;                                                                                                                   
		json_entrust["apiKey"] = users[uidx]->apiKey;                          
		json_entrust["data"] = data;    
		response.clear();                                                                  
		CurlPost(url_entrust, json_entrust.dump(), response);
		std::cout << response << std::endl;
	}

	for (int i = 0; i < users.size(); i++)
		delete users[i];
	for (int i = 0; i < entrusts.size(); i++)
		delete entrusts[i];
	users.clear();
	entrusts.clear();
}

BOOST_AUTO_TEST_SUITE_END()
