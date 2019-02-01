import xlrd
import json
import random

workbook = xlrd.open_workbook("api.xls")

names = workbook.sheet_names()

keysheet = workbook.sheet_by_name('keys')

json_filename = "api_json.json"

json_arr = []

for num in range(2,3)
    json_user = []
    json_data = "TEST1TEST2," + 



for num in range(2,3):
    rows = keysheet.row_values(num)
    obj={
        "pairname": "TEST2TEST1",
        "entrustIdList": "",
		"amount" : "1000",
        "currentPage": "1"
    }
    obj['type'] = str(random.randint(0, 1))
    obj['count'] = str(random.randint(90, 200))
    obj['price'] = str(random.randint(90, 110))
    obj['apiKey'] = rows[0]
    obj['secretKey'] = rows[0]
    obj['FpublicKey'] = rows[2]
    json_arr.append(obj)

f = open(json_filename, 'w')
json.dump(json_arr, f)
