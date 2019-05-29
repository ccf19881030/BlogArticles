## [使用Boost asio实现同步的TCP/IP通信](https://www.cnblogs.com/jiayayao/p/6262573.html)
可以先了解一下[Boost asio基本概念](https://www.cnblogs.com/jiayayao/p/6262081.html)，以下是Boost asio实现的同步TCP/IP通信：
服务器程序部分，如果想保留套接字之后继续通信，可以动态申请socket_type，保存指针，因为socket_type不能拷贝：
```cpp
#include "stdafx.h"
#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace std;

int main()
{
    try
    {
        typedef ip::tcp::acceptor acceptor_type;
        typedef ip::tcp::endpoint endpoint_type;
        typedef ip::tcp::socket socket_type;

        std::cout<<"Server start."<<endl;
        io_service io;
        acceptor_type acceptor(io, endpoint_type(ip::tcp::v4(), 6688));
        std::cout<<acceptor.local_endpoint().address()<<endl;

        for (;;)
        {
            socket_type sock(io);
            acceptor.accept(sock);

            std::cout<<"Client";
            std::cout<<sock.remote_endpoint().address()<<endl;
            sock.send(buffer("Hello asio"));
        }
    }
    catch (std::exception &e)
    {
        std::cout<<e.what()<<endl;
    }

    return 0;
}
```
客户端：
```cpp
#include "stdafx.h"
#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace std;

int main()
{
    try
    {
        typedef ip::tcp::acceptor acceptor_type;
        typedef ip::tcp::endpoint endpoint_type;
        typedef ip::tcp::socket socket_type;
        typedef ip::address address_type;

        std::cout<<"Client start."<<endl;
        io_service io;
        socket_type sock(io);
        endpoint_type ep(address_type::from_string("127.0.0.1"), 6688);

        sock.connect(ep);

        vector<char> str(100, 0);
        boost::system::error_code ec;
        for (;;)//循环接收
        {
            sock.read_some(buffer(str), ec);
            if (ec)
            {
                break;
            }
            cout<<&str[0];
        }
        // 析构自动断开连接
    }
    catch (std::exception &e)
    {
        std::cout<<e.what()<<endl;
    }
    return 0;
}
```
