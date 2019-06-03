## [async_read_some 怎样设置超时返回？](https://bbs.csdn.net/topics/391998593?page=1)
async_read_some 怎样设置超时返回？
```cpp
char g_cData[1024] = {0};
boost::asio::io_service ioservice;
boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("192.168.100.1"),1234);
boost::asio::ip::tcp::socket socket(ioservice);
 
void handle_read(const boost::system::error_code &ec,size_t byte_read) { }
 
void handle_write(const boost::system::error_code &ec,size_t byte_read)
{
        socket.async_read_some(boost::asio::buffer(g_cData),  //Recv   
                boost::bind(handle_read,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}
 
void main()
{       string cmd = "open";
        boost::asio::async_write(socket,boost::asio::buffer(cmd),
            boost::bind(handle_write,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred)
            );
        ioservice.run();
}
```
问题：怎样可以使用定时器dealine_timer设置一个超时时间，让async_read_some()即使没有接收到数据也可以返回呢？

或者有没有其他的办法能够使它结束返回？

async_read_some ()只有收到数据或者出错才会返回，但如果不出错又收不到数据，那么就会一直卡在这里了。
```cpp
// handle_write() 改为以下的
void handle_write(const boost::system::error_code &ec,size_t byte_read)
{
    int cnt = 0;
    for(;;)
    {
        cnt++;
        if(cnt>3) break;  //调用三次async_read_some() 
        socket.async_read_some(boost::asio::buffer(g_cData), //Recv
                boost::bind(handle_read,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
}
```
