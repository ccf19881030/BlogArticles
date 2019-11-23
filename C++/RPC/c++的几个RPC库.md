## [c++的几个RPC库](https://blog.csdn.net/seebit/article/details/6087467)
1. RCF: 纯c++的RPC, 不引入IDL, 大量用到boost，比较强大.
2. casocklib:  protobuf + asio 较完善实现
3. eventrpc: protobuf + libevent 较完善实现
4. evproto: protobuf + libevent 简单实现
5. febird：同样无IDL的c++ RPC，自己实现了串行化和网络IO.
6. libHttp, xmlrpc 都是xml封装的RPC

另外还有apache的两个项目 ：thrift, avro
