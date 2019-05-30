## [BOOST中read_some和 boost::asio::error::eof(2)错误](https://www.cnblogs.com/lovelylife/p/5536229.html)
当socket读写完成调用回调函数时候一定要检查 是不是有EOF错误，如果有那么好了，另一方已经断开连接了别无选择，你也断开吧。
```cpp
for (;;) {
    boost::array < char, 128 > buf;
    boost::system::error_code error;
    size_t len = socket.read_some(boost::asio::buffer(buf), boost::asio::assign_error(error));
    //当服务器关闭连接时,boost::asio::ip::tcp::socket::read_some()会用boost::asio::error::eof标志完成, 这时我们应该退出读取循环了.
    if (error == boost::asio::error::eof)  // Connection closed cleanly by peer.
      break;
    else if (error)  // Some other error.
      throw error;  //如果发生了什么异常我们同样会抛出它
    std::cout.write(buf.data(), len);
}
```关于read_some的理解，有数据可读则会读取最大不超过buffer指定的大小的数据。例如read_some( 1024 个字节), socket的接收中只有128个字节，那就读取尽可能能多的（128字节）数据并返回； 当socket的接收缓冲中有4096个字节，超过指定的1024个字节，则会读取1024个字节并返回。

在异步async_read_some中是一样，回调会立即返回并只调用一次，

原文 [http://blog.chinaunix.net/uid-22273897-id-393662.html](http://blog.chinaunix.net/uid-22273897-id-393662.html)
