import redis
 
r = redis.Redis(host='192.168.0.40', port=7001)
r.set('foo', 'Bar')
print r.get('foo')
