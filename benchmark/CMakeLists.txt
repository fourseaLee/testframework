cmake_minimum_required(VERSION 2.8)

project(benchmark)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE "Debug")


include_directories(../include)


add_executable(benchmark
			   benchmark.cpp
		      ../src/asset_curl.cpp  
			  ../src/common.cpp 
			  ../src/db_mysql.cpp
			  ../src/sync.cpp)	

target_link_libraries(benchmark c rt curl pthread  boost_unit_test_framework boost_program_options boost_system boost_thread celero event  mysqlclient )

