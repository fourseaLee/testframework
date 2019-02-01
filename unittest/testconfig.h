#ifndef TESTCONFIG_H
#define TESTCONFIG_H
#include <string>
#include <vector>
#include "db_mysql.h"

struct UserInfo
{
	std::string apiKey;
	std::string secretKey;
	std::string pubKey;
};

struct EntrustInfo
{
	std::string pairname;
	std::string type;
	std::string price;
	std::string count;
	std::string amount;
};

struct CodePostInfo
{
	std::string Fpublickey;
	std::string secretKey;
	std::string apiKey;
	std::string type;
	std::string price;
	std::string count;
	std::string amount;
};

void decodeUserConfig(std::vector<UserInfo*>& vec,const std::string& file_path);
void decodeEntrustConfig(std::vector<EntrustInfo*>& vec,const std::string& file_path);
void readJsonToCodeInfo(std::vector<CodePostInfo*>& vect_code_info,const std::string& file_path);

void readBaseUrlFromJsonConf(std::string& url_base,const std::string& file_path);

void readUrlFromJsonConf(std::string& url_bron,std::string& url_entrust ,const std::string& file_path);

void readDBConnect(DBMysql::MysqlConnect *connect_db ,const std::string& file_path);

void readDBQuery(std::vector<std::string>&vect_db_query, std::vector<std::string>& vect_query_type,const std::string& file_path);

#endif
