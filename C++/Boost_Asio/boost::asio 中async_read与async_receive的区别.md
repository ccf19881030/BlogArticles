## [boost::asio 中async_read与async_receive的区别](https://my.oschina.net/cppblog/blog/8887?from=rss)
### boost::asio 中async_read与async_receive的区别
现象：在调用async_read后，即使收到数据包，也没有调用相应的ReadHandler 回调函数
```cpp
void handle_connect(const boost::system::error_code & error,
       tcp::resolver::iterator endpoint_iterator)
   {
       if(!error)
       {
           socket_.async_receive(boost::asio::buffer(buf_),            
               boost::bind(&tcp_client::handler_read_response,this,
               boost::asio::placeholders::error,
               boost::asio::placeholders::bytes_transferred));
                       //直到收到的字节数能够填满buf_(即256个字节)或出错，才调用handler_read_responsehandler_read_response;否则即使收到包也不进行处理。

           boost::asio::async_read(socket_,boost::asio::buffer(buf_),
               boost::bind(&tcp_client::handler_read_response,this,
               boost::asio::placeholders::error,
               boost::asio::placeholders::bytes_transferred));
                     //一旦收到数据或出错，就调用handler_read_response
       }
}
tcp::socket socket_;
boost::array buf_;
void handler_read_response(const boost::system::error_code & error, size_t /*bytes_transferred*/) //注意类型，error有引用，而bytes_transferred没有引用
```

//声明：boost/asio/read.hpp
```cpp
template     
void async_read(AsyncReadStream& s, const MutableBufferSequence& buffers,
    ReadHandler handler);

//定义: boost/asio/impl/read.hpp
* @code void handler(
*   const boost::system::error_code& error, // Result of operation.
*
*   std::size_t bytes_transferred           // Number of bytes copied into the
*                                           // buffers. If an error occurred,
*                                           // this will be the  number of
*                                           // bytes successfully transferred
*                                           // prior to the error.
* );
template 
    typename ReadHandler>
inline void async_read(AsyncReadStream& s, const MutableBufferSequence& buffers,
    ReadHandler handler)
{
 async_read(s, buffers, transfer_all(), handler);
}
* @par Example
* To read into a single data buffer use the @ref buffer function as follows:
* @code boost::asio::async_read(s,
*     boost::asio::buffer(data, size),
*     boost::asio::transfer_at_least(32),
*     handler); @endcode
* See the @ref buffer documentation for information on reading into multiple
* buffers in one go, and how to use it with arrays, boost::array or
* std::vector.
*/
template 
    typename CompletionCondition, typename ReadHandler>
void async_read(AsyncReadStream& s, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition, ReadHandler handler);

 template 
 void async_receive(const MutableBufferSequence& buffers, ReadHandler handler)
 {
    this->service.async_receive(this->implementation, buffers, 0, handler);
 }
```
### 结论：
async_receive包含有CompletionCondition， 在调用
void async_read(AsyncReadStream& s, const MutableBufferSequence& buffers,ReadHandler handler)时，必须等到填满Buffer，否则即使收到数据包，也不会没有调用ReadHandler句柄；
async_read只要收到数据，就会被调用
