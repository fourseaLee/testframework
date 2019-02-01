import threading
import time
import redis

redis_connect = redis.Redis(host='192.168.0.45',port=6379)

mutex = threading.Lock()

def lock_redis(lock_key,lock_value):
    redis_connect.set(lock_key,lock_value)
    
def set_redis(redis_key,redis_value):
    lock_key = str(redis_key) +"lock"
    lock_value = redis_connect.get(lock_key)
    if lock_value == 0:
        mutex.acquire()
        lock_redis(lock_key,1)
        redis_connect.set(redis_key,redis_value)
        lock_redis(lock_key,0)
        mutex.release()
    else:
        print 'the key %s is changing!'%redis_key 

def thread_redis(redis_key,redis_value):
	set_redis(redis_key,redis_value)

def action(arg):
    time.sleep(1)
    print 'sub thread start!the thread name is:%s\r'%threading.currentThread().getName()
    time.sleep(1)

for i in xrange(10):
    t = threading.Thread(target=thread_redis,args=(i%4,"test"))
    t.start()

print "main_thread end"
