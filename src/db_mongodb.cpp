#include "db_mongodb.h"
#include <iostream>
#include <bsoncxx/types.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/instance.hpp>


DBMongodb::DBMongodb()
{
}

DBMongodb::~DBMongodb()
{
}


void DBMongodb::SetUrl(const std::string& url)
{
	mongodb_url_ = url;	
}


bool DBMongodb::CreateCollection(const Collection& collection)
{
	
}


bool DBMongodb::InsertCollection(const Collection& collection)
{
	mongocxx::instance inst{};
	mongocxx::client conn{mongocxx::uri{mongodb_url_}};

	bsoncxx::builder::stream::document document{};

	auto collection = conn[collection.db_name][];
	document << "test" << 1;

	try {
		auto result = collection.insert_one(document.view());

		// Currently, result will always be true (or an exception will be
		// thrown).  Eventually, unacknowledged writes will give a false
		// result. See https://jira.mongodb.org/browse/CXX-894

		if (!result) {
			std::cout << "Unacknowledged write. No id available." << std::endl;
			return EXIT_SUCCESS;
		}

		if (result->inserted_id().type() == bsoncxx::type::k_oid) {
			bsoncxx::oid id = result->inserted_id().get_oid().value;
			std::string id_str = id.to_string();
			std::cout << "Inserted id: " << id_str << std::endl;
		} else {
			std::cout << "Inserted id was not an OID type" << std::endl;
		}
	} catch (const mongocxx::exception& e) {
		std::cout << "An exception occurred: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;


}

bool DBMongodb::UpdateCollection(const Collection& collection)
{

}


bool DBMongodb::InsertDocument(const Collection& collection, const std::string& content )
{

}

bool DBMongodb::UpdateDocument(const Collection& collection,const std::string& content)
{

}




