How make it?
cd  bin/ &&  cmake ../ && make
This is unit testing  for test exchange.

Naming mode is like :
The file (*.cpp) of  prefix starting with "test_" is a test fixture . 
The name of fixture  is  *.cpp name without "test_"  prefix and adds  suffix "_test".
example:
The file of name "test_asset_curl.cpp" is  a fixture of  unit_test.
Its fixture name is "asset_curl_test".

If you would run the test case of the fixture , you can cmd like this: 

run all test case.
./util_test  --run_test=asset_curl_test

run all test case with boost unit test log.
./util_test  --log_level=all --run_test=asset_curl_test


run the test case("wangTest")  of test fixture("asset_curl_test")

./util_test --run_test=asset_curl_test/wangTest

Run  util_test --help   for the full list.

