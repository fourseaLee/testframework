#ifndef  ASSET_CURL_H
#define  ASSET_CURL_H
#include <string>


bool CurlRequest(const std::string& request_url, const std::string&request_auth, const std::string& request_data, std::string& response);

bool CurlPost(const std::string& post_url, const std::string& post_data,std::string& response);

#endif
