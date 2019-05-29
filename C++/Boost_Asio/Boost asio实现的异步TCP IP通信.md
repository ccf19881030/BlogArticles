## [Boost asio实现的异步TCP/IP通信](https://www.jianshu.com/p/68a409f43659)
asio库基于操作系统提供的异步机制，采用前摄器模式（Proactor）实现可移植的异步（或同步）IO操作，不需要使用多线程和锁，有效避免多线程编程带来的诸多有害副作用（如竞争，死锁）。
asio封装了操作系统的select、kqueue、poll/epoll、overlapped I/O等机制，实现异步IO模型。在同步模式下，程序发起一个IO操作，向io_service提交请求，io_service把操作转交给操作系统，同步地等待。当IO操作完成时，操作系统通知io_service，然后io_service再把结果发回给程序，完成整个同步流程。在异步模式下，程序除了要发起IO操作，还要定义一个用于回调的完成处理函数。io_service同样把IO操作转交给操作系统执行，但它不同步等待，而是立即返回。调用io_service的run()成员函数可以等待异步操作完成，当异步操作完成时io_service从操作系统获取结果，在调用handler执行后续逻辑。
Boost asio实现的异步TCP/IP通信：
```cpp
#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

int main(int argc, char const *argv[])
{
    io_service iosev; 
    ip::tcp::acceptor acceptor(iosev, ip::tcp::endpoint(ip::tcp::v4(), 1000));
    for(;;){
        ip::tcp::socket socket(iosev);
        acceptor.accept(socket);
        std::cout<<socket.remote_endpoint().address()<<std::endl; 
        boost::system::error_code ec; 
        socket.write_some(buffer("hello world1"), ec);

        if(ec){
            std::cout<<boost::system::system_error(ec).what()<<std::endl; 
            break; 
        }
    }
    return 0;
}
```
服务端文件asioServer.cpp 编译
```shell
g++  -o asioServer asioServer.cpp -lboost_system
```
异步客户端代码：
```cpp
#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio; 

int main(int argc, char const *argv[])
{
    io_service iosev; 
    ip::tcp::socket socket(iosev);
    ip::tcp::endpoint ep(ip::address_v4::from_string("127.0.0.1"), 1000);

    boost::system::error_code ec; 
    socket.connect(ep, ec);
    if(ec){
        std::cout<<boost::system::system_error(ec).what()<<std::endl; 
        return -1; 
    }

    char buf[100];
    size_t len = socket.read_some(buffer(buf), ec);
    std::cout.write(buf, len);

    return 0;
}
```
客户端编译asioClient.cpp :
```shell
g++ -o asioClient asioClient.cpp -lboost_system
```
