//
// chat_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
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
		tcp::endpoint endpoint = *endpoint_iterator;
		socket_.async_connect(endpoint,
			boost::bind(&chat_client::handle_connect, this,
				boost::asio::placeholders::error, ++endpoint_iterator));
	}

	void write(const chat_message& msg)
	{
		io_service_.post(boost::bind(&chat_client::do_write, this, msg));
	}

	void close()
	{
		io_service_.post(boost::bind(&chat_client::do_close, this));
	}

private:

	void handle_connect(const boost::system::error_code& error,
		tcp::resolver::iterator endpoint_iterator)
	{
		if (!error)
		{
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.data(), chat_message::header_length),
				boost::bind(&chat_client::handle_read_header, this,
					boost::asio::placeholders::error));
		}
		else if (endpoint_iterator != tcp::resolver::iterator())
		{
			socket_.close();
			tcp::endpoint endpoint = *endpoint_iterator;
			socket_.async_connect(endpoint,
				boost::bind(&chat_client::handle_connect, this,
					boost::asio::placeholders::error, ++endpoint_iterator));
		}
	}

	void handle_read_header(const boost::system::error_code& error)
	{
		if (!error && read_msg_.decode_header())
		{
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
				boost::bind(&chat_client::handle_read_body, this,
					boost::asio::placeholders::error));
		}
		else
		{
			do_close();
		}
	}

	void handle_read_body(const boost::system::error_code& error)
	{
		if (!error)
		{
			std::cout.write(read_msg_.body(), read_msg_.body_length());
			std::cout << "\n";
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.data(), chat_message::header_length),
				boost::bind(&chat_client::handle_read_header, this,
					boost::asio::placeholders::error));
		}
		else
		{
			do_close();
		}
	}

	void do_write(chat_message msg)
	{
		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg);
		if (!write_in_progress)
		{
			boost::asio::async_write(socket_,
				boost::asio::buffer(write_msgs_.front().data(),
					write_msgs_.front().length()),
				boost::bind(&chat_client::handle_write, this,
					boost::asio::placeholders::error));
		}
	}

	void handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{
			write_msgs_.pop_front();
			if (!write_msgs_.empty())
			{
				boost::asio::async_write(socket_,
					boost::asio::buffer(write_msgs_.front().data(),
						write_msgs_.front().length()),
					boost::bind(&chat_client::handle_write, this,
						boost::asio::placeholders::error));
			}
		}
		else
		{
			do_close();
		}
	}

	void do_close()
	{
		socket_.close();
	}

private:
	boost::asio::io_service& io_service_;
	tcp::socket socket_;
	chat_message read_msg_;
	chat_message_queue write_msgs_;
};

int main(int argc, char* argv[])
{
	//客户端需要两个线程
   //主线程负责读取标准输入
   //thread线程负责调度异步事件(io_service.run())

	try
	{
#if 0
		if (argc != 3)
		{
			std::cerr << "Usage: chat_client <host> <port>\n";
			return 1;
		}
#endif
		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
#if 0
		//tcp::resolver::query query(argv[1], argv[2]);
#endif
		
		auto endpoint_iterator = resolver.resolve({ "127.0.0.1", "9001" });
		chat_client c(io_service, endpoint_iterator);	// 客户端

		// 启动线程执行io_service.run()
		boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));

		char line[chat_message::max_body_length + 1];
		// 读取标准输入
		//客户端读取数据后，进行简单的编码（消息格式为固定4个字节的header和body），
		// 然后发起异步连接，写入网络套接字。
		while (std::cin.getline(line, chat_message::max_body_length + 1))
		{
			using namespace std; // For strlen and memcpy.
			// 将用户输入的数据组成消息包（消息头长度4bytes+消息体，消息体最多512bytes）
			chat_message msg;
			// 设置消息体的长度
			msg.body_length(strlen(line));	// 获取header消息
			// 拷贝消息体
			memcpy(msg.body(), line, msg.body_length());
			// 设置消息体的头长度
			msg.encode_header();	// 对消息进行编码
			// 发送消息
			c.write(msg);
		}

		c.close();
		t.join();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	getchar();

	return 0;
}
