## boost::asio::deadline_timer 定时器的用法
### ASIO，基于操作系统的异步机制，可有效避免多线程编程的诸多副作用。
目前主要关注于通信方面，使用大量的类封装了socket，提供更高层次的接口。使用不需要编译，默认不支持SSL，要支持的话需要自己编译OpenSSL。
### boost::asio::deadline_timer 定时器 用法Sample
```cpp
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/bind.hpp>
using namespace boost;
 
void async_timer_callback(asio::deadline_timer* async_timer, int async_count, const system::error_code& err)
{
	if (err)
		std::cout << "async_timer.async_wait err = " << err.message() << std::endl;
	else
	{
		std::cout << "async_timer async_count = " << async_count << " now expires expires_from_now = " << async_timer->expires_from_now() << std::endl;
		if (--async_count > 0)
		{
			async_timer->expires_at(async_timer->expires_at() + posix_time::milliseconds(500));
			async_timer->async_wait(boost::bind(async_timer_callback, async_timer, async_count, asio::placeholders::error));
		}
	}
}
 
int main()
{
	asio::io_service ios;
	// 同步等待
	asio::deadline_timer timer(ios, posix_time::seconds(2));
	std::cout << "timer expires_at = " << timer.expires_at() << " expires_from_now = "<<timer.expires_from_now()<<std::endl;
 
	timer.wait();
	std::cout << "timer now expires expires_from_now = " << timer.expires_from_now() << std::endl;
 
	// 异步等待
	asio::deadline_timer async_timer(ios, posix_time::milliseconds(500));
	std::cout << "async_timer expires_at = " << async_timer.expires_at() << " expires_from_now = " << async_timer.expires_from_now() << std::endl;
 
	int async_count = 5;
	async_timer.async_wait(boost::bind(async_timer_callback, &async_timer, async_count, asio::placeholders::error));
	
	system::error_code err;
	ios.run(err);
	if (err)
	{
		std::cout << "ios.run err = " << err.message() << std::endl;
	}
	else
	{
		std::cout << "ios.run done " << std::endl;
	}
	return 0;
}
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/bind.hpp>
using namespace boost;
 
void async_timer_callback(asio::deadline_timer* async_timer, int async_count, const system::error_code& err)
{
	if (err)
		std::cout << "async_timer.async_wait err = " << err.message() << std::endl;
	else
	{
		std::cout << "async_timer async_count = " << async_count << " now expires expires_from_now = " << async_timer->expires_from_now() << std::endl;
		if (--async_count > 0)
		{
			async_timer->expires_at(async_timer->expires_at() + posix_time::milliseconds(500));
			async_timer->async_wait(boost::bind(async_timer_callback, async_timer, async_count, asio::placeholders::error));
		}
	}
}
 
int main()
{
	asio::io_service ios;
	// 同步等待
	asio::deadline_timer timer(ios, posix_time::seconds(2));
	std::cout << "timer expires_at = " << timer.expires_at() << " expires_from_now = "<<timer.expires_from_now()<<std::endl;
 
	timer.wait();
	std::cout << "timer now expires expires_from_now = " << timer.expires_from_now() << std::endl;
 
	// 异步等待
	asio::deadline_timer async_timer(ios, posix_time::milliseconds(500));
	std::cout << "async_timer expires_at = " << async_timer.expires_at() << " expires_from_now = " << async_timer.expires_from_now() << std::endl;
 
	int async_count = 5;
	async_timer.async_wait(boost::bind(async_timer_callback, &async_timer, async_count, asio::placeholders::error));
	
	system::error_code err;
	ios.run(err);
	if (err)
	{
		std::cout << "ios.run err = " << err.message() << std::endl;
	}
	else
	{
		std::cout << "ios.run done " << std::endl;
	}
	return 0;
}
```
### 运行的结果
```shell
timer expires_at = 2016-Sep-25 08:19:35.318075 expires_from_now = 00:00:02
timer now expires expires_from_now = -00:00:00.000694
async_timer expires_at = 2016-Sep-25 08:19:35.820758 expires_from_now = 00:00:00.500000
async_timer async_count = 5 now expires expires_from_now = -00:00:00.000550
async_timer async_count = 4 now expires expires_from_now = -00:00:00.000476
async_timer async_count = 3 now expires expires_from_now = -00:00:00.000748
async_timer async_count = 2 now expires expires_from_now = -00:00:00.000643
async_timer async_count = 1 now expires expires_from_now = -00:00:00.000445
ios.run done
```

