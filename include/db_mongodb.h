#ifndef DB_MONGODB_H
#define DB_MONGODB_H
#include <string>


class DBMongodb
{
public:
	DBMongodb();
	~DBMongodb();
	void SetUrl(std::string url);


public:

	struct Collection
	{
		std::string db_name;
		std::string collection_name;
		std::string collection_content;
	};

	bool CreateCollection(const Collection& collection);

	bool InsertCollection(const Collection& collection);

	bool UpdateCollection(const Collection& collection);

public:
	
	bool InsertDocument(const Collection& collection, const std::string& content);

	bool UpdateDocument(const Collection& collection, const std::string& content);

private:
	std::string mongodb_url_;

}





#endif
