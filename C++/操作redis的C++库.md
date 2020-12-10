关于redis的C++库我一般使用的[hiredis](https://github.com/redis/hiredis)，不过hiredis对于Linux的比较友好，如果需要Windows下使用hiredis库的话，可以参考redis windows版：
GitHub上的MSOpenTech/redis项目地址- [https://github.com/MSOpenTech/redis](https://github.com/MSOpenTech/redis)
redis-plus-plus: [https://github.com/sewenew/redis-plus-plus](https://github.com/sewenew/redis-plus-plus)
可以从redis官网[https://redis.io/clients#c-plus-plus](https://redis.io/clients#c-plus-plus)上看到目前推荐使用的redis的C++客户端库是：[redis-plus-plus](https://github.com/sewenew/redis-plus-plus)
redis-plus-plus is a Redis client, based on hiredis and written in C++11. It supports scritpting, pub/sub, pipeline, transaction, Redis Cluster, Redis Sentinel, connection pool, ACL, SSL and thread safety.
