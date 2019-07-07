## [boost写的异步客户端样例代码修改为支持断开重连的代码](https://www.cnblogs.com/luhouxiang/p/11084266.html)
考虑到boost的工业级强度，因此就直接用了，代码的官方示例地址：https://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/examples/cpp11_examples.html

用起来还是挺方便的，代码量少，稳定性高，速度快。

后来实际过程中希望能支持断开生连的功能，比如客户端先启动，服务器后启动，希望服务器起来后，客户端立即连上去。网络波动的情况下，客户端有可能断开，断开后立即再连接上去。

原有的示例代码不能实现以上两个功能，经过研究发现异步连接时，如果成功才进行do_read_header(),那不成功时再进行do_connect即可

然后在类中设置一个连接标识is_connected_, 当发生断开时，将连接标识置为false,外部不断检测此标识，发现标识为false，则重新启动整个客户端即可

修改的完整代码， 需要服务器测试请到刚开始给的网址去下载：
```cpp
//
// chat_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// https://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/examples/cpp11_examples.html

#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include "chat_message.hpp"

using boost::asio::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;

class chat_client
{
public:
    chat_client(boost::asio::io_service& io_service,
        tcp::resolver::iterator endpoint_iterator)
        : io_service_(io_service),
        socket_(io_service)
    {
        is_connected_ = false;
        do_connect(endpoint_iterator);
    }

    void write(const chat_message& msg)
    {
        io_service_.post(
            [this, msg]()
        {
            bool write_in_progress = !write_msgs_.empty();
            write_msgs_.push_back(msg);
            if (!write_in_progress)
            {
                do_write();
            }
        });
    }

    void close()
    {
        io_service_.post([this]() { close_socket(); });
    }

    bool get_connected() const {
        return is_connected_;
    }

private:
    void do_connect(tcp::resolver::iterator endpoint_iterator)
    {
        boost::asio::async_connect(socket_, endpoint_iterator,
            [this, endpoint_iterator](boost::system::error_code ec, tcp::resolver::iterator)
        {
            if (!ec)
            {
                is_connected_ = true;
                do_read_header();
            }
            else {
                do_connect(endpoint_iterator);
            }
        });
    }

    void do_read_header()
    {
        boost::asio::async_read(socket_,
            boost::asio::buffer(read_msg_.data(), chat_message::header_length),
            [this](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec && read_msg_.decode_header())
            {
                do_read_body();
            }
            else
            {
                close_socket();
            }
        });
    }

    void close_socket()
    {
        socket_.close();
        is_connected_ = false;
    }

    void do_read_body()
    {
        boost::asio::async_read(socket_,
            boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
            [this](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                std::cout.write(read_msg_.body(), read_msg_.body_length());
                std::cout << "\n";
                do_read_header();
            }
            else
            {
                close_socket();
            }
        });
    }

    void do_write()
    {
        boost::asio::async_write(socket_,
            boost::asio::buffer(write_msgs_.front().data(),
                write_msgs_.front().length()),
            [this](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                write_msgs_.pop_front();
                if (!write_msgs_.empty())
                {
                    do_write();
                }
            }
            else
            {
                close_socket();
            }
        });
    }

private:
    bool is_connected_;
    boost::asio::io_service& io_service_;
    tcp::socket socket_;
    chat_message read_msg_;
    chat_message_queue write_msgs_;
};

int main(int argc, char* argv[])
{

    if (argc != 3)
    {
        std::cerr << "Usage: chat_client <host> <port>\n";
        return 1;
    }
    while (true)
    {
        try
        {
            boost::asio::io_service io_service;

            tcp::resolver resolver(io_service);
            auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });
            chat_client c(io_service, endpoint_iterator);

            std::thread t([&io_service]() { io_service.run(); });

            //         char line[chat_message::max_body_length + 1];
            //         while (std::cin.getline(line, chat_message::max_body_length + 1))
            //         {
            //             chat_message msg;
            //             msg.body_length(std::strlen(line));
            //             std::memcpy(msg.body(), line, msg.body_length());
            //             msg.encode_header();
            //             c.write(msg);
            //         }
            while (c.get_connected())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }

            c.close();
            t.join();
        }
        catch (std::exception& e)
        {
            std::cerr << "Exception: " << e.what() << "\n";
        }
    }


    return 0;
}
```
## [C++11 Examples](https://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/examples/cpp11_examples.html)
