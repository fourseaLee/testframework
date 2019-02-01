#include "testconfig.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
using json = nlohmann::json;

static void  setJsonFromFile(const std::string &file_path, json&json_data)
{
	std::ifstream jfile(file_path);
	if (!jfile)
	{
		std::cout << "open user.conf failed!" << std::endl;
		return;
	}
	//json json_data;
	jfile >> json_data;
	jfile.close();
}

void decodeUserConfig(std::vector<UserInfo*>& vec, const std::string& file_path)
{
	//std::string file_path = "../conf/user.conf" ;
	json json_data;
	setJsonFromFile(file_path,json_data);
	for (int i = 0; i < json_data.size(); i++)
	{
		UserInfo* info = new UserInfo();
		json temp = json_data.at(i);
		info->apiKey = temp.at(0).get<std::string>();
		info->secretKey = temp.at(1).get<std::string>();
		info->pubKey = temp.at(2).get<std::string>();
		vec.push_back(info);
	}
}

void decodeEntrustConfig(std::vector<EntrustInfo*>& vec,const std::string& file_path)
{
	//	std::string file_path = "../conf/entrust.conf" ;
	json json_data;
	setJsonFromFile(file_path,json_data);
	for (int i = 0; i < json_data.size(); i++)
	{
		EntrustInfo* info = new EntrustInfo();
		json temp = json_data.at(i);
		info->pairname = temp.at(0).get<std::string>();
		info->type = temp.at(1).get<std::string>();
		info->price = temp.at(2).get<std::string>();
		info->count = temp.at(3).get<std::string>();
		info->amount = temp.at(4).get<std::string>();
		vec.push_back(info);
	}
}

void readJsonToCodeInfo(std::vector<CodePostInfo*>& vect_code_info,const std::string& file_path)
{
	//	std::string file_path = "../conf/taiwan.conf" ;
	json json_data;
	setJsonFromFile(file_path,json_data); 
	for (int i = 0; i < json_data.size(); i++)
	{
		CodePostInfo* pCodeInfo = new CodePostInfo();
		json temp = json_data.at(i);
		pCodeInfo->Fpublickey = temp["Fpublickey"].get<std::string>();
		pCodeInfo->secretKey = temp["secretKey"].get<std::string>();
		pCodeInfo->apiKey = temp["apiKey"].get<std::string>();
		pCodeInfo->type = temp["type"].get<std::string>();
		pCodeInfo->price = temp["price"].get<std::string>();
		pCodeInfo->count = temp["count"].get<std::string>();
		pCodeInfo->amount = temp["amount"].get<std::string>();
		vect_code_info.push_back(pCodeInfo);
	}

}

void readUrlFromJsonConf(std::string& url_bron,std::string& url_entrust ,const std::string& file_path)
{
	json json_data;
	setJsonFromFile(file_path,json_data); 
	url_bron = json_data["url_bron"].get<std::string>();
	url_entrust = json_data["url_entrust"].get<std::string>();
}
void readDBConnect(DBMysql::MysqlConnect *connect_db ,const std::string& file_path)
{
	json json_data;
	setJsonFromFile(file_path,json_data);
	connect_db->url = json_data["url"].get<std::string>();
	connect_db->port = json_data["port"].get<int>();
	connect_db->user_name = json_data["user_name"].get<std::string>();
	connect_db->user_pass = json_data["user_pass"].get<std::string>();
	connect_db->use_db = json_data["user_db"].get<std::string>();
}
void readDBQuery(std::vector<std::string>& vect_db_query , std::vector<std::string>& vect_query_type,const std::string& file_path)
{
	json json_data;
	setJsonFromFile(file_path,json_data);
	for (int i = 0; i < json_data.size(); i++)
	{
		json temp = json_data.at(i);
		std::string str_sql_query = temp.at(0).get<std::string>();
		std::string str_query_type = temp.at(1).get<std::string>();
		vect_db_query.push_back(str_sql_query);
		vect_query_type.push_back(str_query_type);
	}
}

void readBaseUrlFromJsonConf(std::string& url_base,const std::string& file_path)
{
	json json_data;
	setJsonFromFile(file_path,json_data);
	url_base = json_data["url_base"].get<std::string>();

}
