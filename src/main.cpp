#include "sync.h"
#include "checkqueue.h"
#include <boost/thread/thread.hpp>
#include "task_check.h"
#include "easylogging++.h"
#include <cpp_redis/cpp_redis>
#include <iostream>
#include <cstdlib>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/make_unique.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/logger.hpp>
#include <mongocxx/options/client.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/types.hpp>
#include <chrono>
INITIALIZE_EASYLOGGINGPP


using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::finalize;

int main(int, char**) {
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{ "mongodb://192.168.0.40:27017"}};

    auto db = conn["test"];

    // TODO: fix dates

    // @begin: cpp-insert-a-document
    bsoncxx::document::value restaurant_doc =
        document{} << "address" << open_document << "street"
                   << "2 Avenue"
                   << "zipcode"
                   << "10075"
                   << "building"
                   << "1480"
                   << "coord" << open_array << -73.9557413 << 40.7720266 << close_array
                   << close_document << "borough"
                   << "Manhattan"
                   << "cuisine"
                   << "Italian"
                   << "grades" << open_array << open_document << "date"
                   << bsoncxx::types::b_date{std::chrono::milliseconds{12323}} << "grade"
                   << "A"
                   << "score" << 11 << close_document << open_document << "date"
                   << bsoncxx::types::b_date{std::chrono::milliseconds{121212}} << "grade"
                   << "B"
                   << "score" << 17 << close_document << close_array << "name"
                   << "Vella"
                   << "restaurant_id"
                   << "41704620" << finalize;

    // We choose to move in our document here, which transfers ownership to insert_one()
    auto res = db["restaurants"].insert_one(std::move(restaurant_doc));
}
/*
int main(int argc,char*argv[])
{

	using bsoncxx::builder::stream::document;
	using bsoncxx::v_noabi::builder::basic::kvp;
	mongocxx::instance inst;

	try {
		const auto uri = mongocxx::uri{ "mongodb://192.168.0.40:27017"};

		auto client = mongocxx::client{uri};
		auto admin = client["admin"];
		document ismaster;
		ismaster << "isMaster" << 1;

		auto result = admin.run_command(ismaster.view());
//		std::cout << result << std::endl;

		return EXIT_SUCCESS;
	} catch (const std::exception& xcp) {
		std::cout << "connection failed: " << xcp.what() << std::endl;
		return EXIT_FAILURE;
	}

*/


/*	boost::thread_group threadGroup;
	CCheckQueue<TaskCheck> task_check_queue(128);
	CCheckQueueControl<TaskCheck> control(&task_check_queue);

	for (int i=0; i<5; i++)
		threadGroup.create_thread(boost::bind(&CCheckQueue<TaskCheck>::Thread, boost::ref(task_check_queue)));


	for(int i = 0; i < 20; i++) 
	{
		std::vector<TaskCheck> vChecks;
		TaskCheck check;	
		vChecks.push_back(TaskCheck());
		check(i+1,i*i);
	//	vChecks.push_back(TaskCheck(i+1,i*i));
		check.swap(vChecks.back());
		control.Add(vChecks);
	}

		
	control.Wait();

	threadGroup.interrupt_all();
	threadGroup.join_all();
 */
	//! Enable logging


/*
	cpp_redis::active_logger = std::unique_ptr<cpp_redis::logger>(new cpp_redis::logger);

	cpp_redis::client client;

	client.connect("192.168.0.45", 6379, [](const std::string& host, std::size_t port, cpp_redis::client::connect_state status) {
			if (status == cpp_redis::client::connect_state::dropped) {
			std::cout << "client disconnected from " << host << ":" << port << std::endl;
			}
			});

	// same as client.send({ "SET", "hello", "42" }, ...)
	client.set("hello", "42", [](cpp_redis::reply& reply) {
			std::cout << "set hello 42: " << reply << std::endl;
			// if (reply.is_string())
			//   do_something_with_string(reply.as_string())
			});

	// same as client.send({ "DECRBY", "hello", 12 }, ...)
	client.decrby("hello", 12, [](cpp_redis::reply& reply) {
			std::cout << "decrby hello 12: " << reply << std::endl;
			// if (reply.is_integer())
			//   do_something_with_integer(reply.as_integer())
			});

	// same as client.send({ "GET", "hello" }, ...)
	client.get("hello", [](cpp_redis::reply& reply) {
			std::cout << "get hello: " << reply << std::endl;
			// if (reply.is_string())
			//   do_something_with_string(reply.as_string())
			});

	// commands are pipelined and only sent when client.commit() is called
	// client.commit();

	// synchronous commit, no timeout
	client.sync_commit();
*/
/*	return 0;
}*/
