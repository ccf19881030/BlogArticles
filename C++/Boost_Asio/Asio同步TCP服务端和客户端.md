## [Boost.Asio——（7）同步TCP服务端和客户端](https://www.jianshu.com/p/929a67cecea7)
### 1、服务端源码
```cpp
#include "stdafx.h"
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
    //出现错误  C4996   'ctime': This function or variable may be unsafe.Consider using ctime_s instead.To disable deprecation
    //是因为这个用法不安全，在属性管理器——C/C++ —— 预处理器 添加 _CRT_SECURE_NO_WARNINGS

}

int main()
{
    try
    {
        boost::asio::io_service io_service;
        //设定ip
        std::string address = "192.168.1.15";
        boost::asio::ip::address add;
        add.from_string(address);
        //初始化endpoint
        tcp::acceptor acceptor(io_service, tcp::endpoint(add, 6300));
        std::cout << "ip:" << address << "  port:" << 6300 << std::endl;

        for (;;)
        {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            std::string message = make_daytime_string();

            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
```
### 2、客户端源码
```cpp
#include "stdafx.h"
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

//因为这个程序要接入一个时间服务器，所以需要用户去指定服务器
int main(int argc, char* argv[])
{
    
    try
    {
        /*if (argc != 2)
        {
            std::cerr << "Usage: client <host>" << std::endl;
            
            return 1;
        }*/
        
        
        //使用asio需要指定至少一个io服务
        boost::asio::io_service io_service;

        //将io_service转换为一个TCP节点
        tcp::resolver resolver(io_service);
        //建立一个查询，第一个参数是要查询的服务器，第二个参数是端口，

        //这里第一个参数原本使用的是argv[1]，从命令行启动程序，命令<tcpclient 192.168.1.15>
        //int main(int argc, char* argv[]) 第一个参数获取的是命令行中输入的参数个数，第二个参数是存储的参数的首地址，第一个参数就是argv[1]，第二个是argv[2]
        tcp::resolver::query query("192.168.1.15", "6300");
        //std::cout << argv[1] << std::endl;                //查看输入的服务器地址
        //使用迭代器接收返回，有时候会查到若干个正在监听的服务器


        //也可以直接设定endpoint
        /*boost::system::error_code error = boost::asio::error::host_not_found;
        boost::asio::ip::address add;
        add.from_string("127.0.0.1");
        tcp::endpoint endpoint(add, short(9000));
        socket.connect(endpoint, error);*/


        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        tcp::resolver::iterator end;
        
        //建立一个socket并且连接它
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        //输出查看所有查询到的服务器
        while (endpoint_iterator != end)
        {
            boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator++;
            std::cout << endpoint << std::endl;
        }

        //连接建立之后，我们需要做的就是读取服务器的回复了
        for (;;)
        {
            //使用array存储数据，使用boost::asio::buffer自动决定array大小防止缓存溢出
            boost::array<char, 128> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            //服务器关闭，客户端自动退出
            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            std::cout.write(buf.data(), len);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
```
