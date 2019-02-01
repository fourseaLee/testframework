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

BOOST_FIXTURE_TEST_SUITE(quantization_test,TestingSetup)

BOOST_AUTO_TEST_CASE(cancel_cus_test)
{
	std::string file_cancel_param = "../conf/cancle_param.conf";
	std::string file_url = "../conf/url.conf";
	std::string base_url;
	readBaseUrlFromJsonConf(base_url,file_url);
	std::string funciton_url;
	
	std::string code_url = base_url  + "";
	function_url = base_url + "entrustBatchCancelCus";

}
BOOST_AUTO_TEST_SUITE_END()
