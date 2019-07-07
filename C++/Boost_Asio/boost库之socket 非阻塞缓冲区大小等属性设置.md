## [boost库之socket 非阻塞/缓冲区大小等属性设置](https://blog.csdn.net/wojiuguowei/article/details/78773686)
asio socket 非阻塞/缓冲区大小等属性设置
```cpp
ip::tcp::socket m_socket
 
 //设置阻塞与非阻塞
void SetNoBlock(bool bNoBlock)
{
 if(bNoBlock)
 {
  boost::asio::ip::tcp::socket::non_blocking_io io_option(true);
  m_socket.io_control(io_option);
 }
 else
 {
  //阻塞
  boost::asio::ip::tcp::socket::non_blocking_io io_option(false);
  m_socket.io_control(io_option);
 }
}
//设置发送缓冲区大小
void SetSendBufferSize(int nSize)
{
 boost::asio::socket_base::send_buffer_size size_option(nSize);
 m_socket.set_option(size_option);
}
//设置接收缓冲区大小
void SetRecvBufferSize(int nSize)
{
 boost::asio::socket_base::receive_buffer_size size_option(nSize);
 m_socket.set_option(size_option);
}
socket 端口复用
1).在boost的acceptor类说明中有这样的一个例子。用set_option设置端口是否可复用。
 boost::asio::ip::tcp::acceptor acceptor(io_service);
 boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
 acceptor.open(endpoint.protocol());
 acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
 acceptor.bind(endpoint);
 acceptor.listen();
2).还有一种方法 就是在acceptor的构造函数，下面是acceptor的构造函数，我们看到，第三个参数名reuse_addr 。默认是可以端口复用的，要设置是否复用，也可以通过该处传参。
basic_socket_acceptor(boost::asio::io_service& io_service,const endpoint_type& endpoint, bool reuse_addr = true)
//不停留，不管数据多小都发送到对端。停留，只有数据达到一定大小或者超时时，将数据发送对倒对端。
m_socket.set_option(boost::asio::ip::tcp::no_delay(true));
//保持常连接
m_socket.set_option(boost::asio::socket_base::keep_alive(true));
```
同步连接超时设置，没有对应的set_option参数，asio自带的例子里是用deadline_timer的async_wait方法来实现超时。
1).deadline_timer的async_wait方法
参考：http://blog.csdn.net/li_jian_xing/article/details/50394116
2).传统的Winsock编程可以先把socket设为非阻塞，然后connect，通过boost::asio::ip::tcp::socket类的native函数获取到原始sokcet，再用select来判断超时，asio也可以这样做，唯一“非主流”的是asio里没有一个类似select的函数，所以得调用原始的Winsock API，也就牺牲了跨平台。
参考：http://blog.csdn.net/lazy_cc/article/details/7941069
