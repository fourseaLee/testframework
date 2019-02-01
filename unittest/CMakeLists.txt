cmake_minimum_required(VERSION 2.8)

project(unit_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE "Debug")

#link_directories("/home/dev/svn/BasicTestFramework/bin")

#link_libraries(lib_synthetic_test)


include_directories(../include)
#add_executable(util_test
#			  testingsetup.cpp  
#			  test_asset_curl.cpp
#			  test_redis.cpp
#			  )
add_executable(unit_test
			  testingsetup.cpp 
			  testconfig.cpp
			  test_asset_curl.cpp
			  test_concurrent.cpp
			  test_db.cpp
			  ../src/asset_curl.cpp  
			  ../src/common.cpp 
			  ../src/db_mysql.cpp
			  ../src/sync.cpp)
target_link_libraries(unit_test c rt curl pthread  boost_unit_test_framework boost_program_options boost_system boost_thread event  mysqlclient )

