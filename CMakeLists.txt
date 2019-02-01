cmake_minimum_required(VERSION 2.8)

project(synthetic_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE "Debug")

include_directories(./include
					./redlock-cpp/redlock-cpp)

#link_directories("/home/dev/svn/BasicTestFramework/lib")

#link_libraries(redlock)

add_library(lib_synthetic_test
			src/asset_curl.cpp
			src/db_mysql.cpp
			src/common.cpp
			src/sync.cpp
			src/task_check.cpp)


add_executable(synthetic_test
			src/asset_curl.cpp
			src/db_mysql.cpp
			src/common.cpp
			src/sync.cpp
			src/task_check.cpp
			src/main.cpp)
target_link_libraries(synthetic_test c rt curl pthread event mysqlclient boost_program_options boost_system mongocxx bsoncxx cpp_redis tacopie  boost_thread)


add_subdirectory(benchmark)
add_subdirectory(unittest)

