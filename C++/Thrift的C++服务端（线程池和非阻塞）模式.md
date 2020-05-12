## [Thrift的C++服务端（线程池和非阻塞）模式](https://www.cnblogs.com/voipman/p/7519657.html)

### 非阻塞模式
```cpp
#include "RpcServiceHandler.h"
 
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/TToString.h>
 
int main(int argc, char **argv)
{
    RpcServiceHandler *rpcServiceHanlder = new RpcServiceHandler();
 
    int port = CFG()->getInt(kCfgProcPort);
    int workerCount = CFG()->getInt(kCfgProcWCnt);
 
    boost::shared_ptr<RpcServiceHandler> handler(rpcServiceHanlder);
    boost::shared_ptr<TProcessor> processor(new RpcServiceProcessor(handler));
    boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
 
    boost::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(workerCount);
    boost::shared_ptr<PosixThreadFactory> threadFactory = boost::shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
    threadManager->threadFactory(threadFactory);
    threadManager->start();
     
    TNonblockingServer server(processor,   
                              protocolFactory,   
                              port,   
                              threadManager);
 
    std::cout << "Starting the server..." << std::endl;
 
    server.serve();
    return 0;
}
```

### 线程池模式
```cpp
#include "RpcServiceHandler.h"
 
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/TToString.h>
 
int main(int argc, char **argv)
{
    RpcServiceHandler *rpcServiceHanlder = new RpcServiceHandler();
 
    int port = CFG()->getInt(kCfgProcPort);
    int workerCount = CFG()->getInt(kCfgProcWCnt);
 
    boost::shared_ptr<RpcServiceHandler> handler(rpcServiceHanlder);
    boost::shared_ptr<TProcessor> processor(new RpcServiceProcessor(handler));
    boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
 
    boost::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(workerCount);
    boost::shared_ptr<PosixThreadFactory> threadFactory = boost::shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
    threadManager->threadFactory(threadFactory);
    threadManager->start();
     
    TThreadPoolServer server(processor,
                             serverTransport,
                             transportFactory,
                             protocolFactory,
                             threadManager);
 
    std::cout << "Starting the server..." << std::endl;
 
    server.serve();
    return 0;
}
```

### 单独Server模式
```cpp
#include "RpcServiceHandler.h"
 
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/TToString.h>
 
int main(int argc, char **argv)
{
    RpcServiceHandler *rpcServiceHanlder = new RpcServiceHandler();
 
    int port = CFG()->getInt(kCfgProcPort);
 
    boost::shared_ptr<RpcServiceHandler> handler(rpcServiceHanlder);
    boost::shared_ptr<TProcessor> processor(new RpcServiceProcessor(handler));
    boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
 
 
    std::cout << "Starting the server..." << std::endl;
    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
 
    server.serve();
    return 0;
}
```

## [Thrift的TBinaryProtocol二进制协议分析](https://www.cnblogs.com/voipman/p/5125278.html)
