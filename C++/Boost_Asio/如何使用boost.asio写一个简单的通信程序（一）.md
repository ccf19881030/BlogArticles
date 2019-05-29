## [如何使用boost.asio写一个简单的通信程序（一）](https://www.cnblogs.com/qicosmos/p/3461116.html)
boost.asio相信很多人听说过，作为一个跨平台的通信库，它的性能是很出色的，然而它却谈不上好用，里面有很多地方稍不注意就会出错，要正确的用好asio还是需要花一番精力去学习和实践的，本文将通过介绍如何写一个简单的通信程序来告诉读者如何使用asio，希望对asio的初学者有所帮助。由于只是介绍其基本用法，作为例子的简单示例并不考虑很多的业务逻辑和异常处理，只是介绍基本用法，让初学者入门。

　　使用asio容易出错的一个主要原因是因为它是基于proactor模式实现的，asio有很多异步操作接口，这些异步接口稍不注意就会出现莫名奇妙的错误，所以要用好asio的第一步是理解其异步操思想。
### 异步操作思想
用户发起异步事件，asio将这些异步事件投递到一个队列中,用户发起的操作就返回了，io_service::run会处理异步事件队列中的所有的异步事件，它会将这些事件交给操作系统处理，操作系统处理完成之后会丢到asio的事件完成的队列中，io_service发现有完成队列中有完成事件了，就会通知用户处理完成事件。 所以用户要发起一个异步操作需要做三件事：

调用asio异步操作接口，发起异步操作；如：async_connect、async_read、async_write，这些异步接口需要一个回调函数入参，这个回调函数在事件完成时，由io_service触发。
调用io_service::run处理异步事件；发起一个异步操作，必须要保证io_service::run，因为io_service通过一个循环去处理这些异步操作事件的，如果没有事件就会退出，所以要保证异步事件发起之后，io_service::run还在运行。要保证一直run的一个简单办法就是使用io_service::work，它可以保证io_service一直run。
处理异步操作完成事件；在调用异步接口时会传入一个回调函数，这个回调函数就是处理操作完成事件的，比如读完成了，用户需要对这些数据进行业务逻辑的处理。
　　下图描述了一个异步操作的过程：



　　asio的的核心是io_service, 理解了asio异步接口的机制就容易找出使用asio过程中出现的问题了，在这里把一些常见的问题列出来，并分析原因和提出解决方法。

问题1：为什么我发起了异步操作，如连接或者写，对方都没有反应，好像没有收到连接请求或者没有收到数据？ 答案：一个很可能的原因是io_service在异步操作发起之后没有run，解决办法是保持io_service run。
问题2：为什么发送数据会报错？ 答案：一个可能的原因是发送的数据失效了，异步发送要求发送的数据在回调完成之前都有效，异步操作只是将异步事件句柄投递到io_service队列中就返回了，并不是阻塞的，不注意这一点，如果是临时变量的数据，出了作用域就失效了，导致异步事件还没完成时数据就失效了。解决办法，保证发送数据在事件完成之前一直有效。
问题3：为什么监听socket时，会报“函数不正确”的异常？ 答案：因为监听时，也要保证这个socket一直有效，如果是一个临时变量socket，在调用异步监听后超出作用域就失效了，解决办法，将监听的socket保存起来，使它的生命周期和acceptor一样长。
问题4：为什么连续调用异步操作时会报错？ 答案：因为异步操作必须保证当前异步操作完成之后再发起下一次异步操作。解决办法：在异步完成事件处理完成之后再发起新的异步操作即可。
问题5：为什么对方半天收不到数据，过了半天才一下子收到之前发送的数据？ 答案：因为socket是流数据，一次发送多少数据不是外界能控制的，这也是所谓的粘包问题。解决办法，可以在接收时指定至少收多少的条件，或者做tcp分包处理。
　　说了这么多，还是来看看例子吧，一个简单的通信程序：服务端监听某个端口，允许多个客户端连接上来，服务器将客户端发来的数据打印出来。 先看看服务端的需求，需求很简单，第一，要求能接收多个客户端；第二，要求把收到的数据打印出来。

　　要求能接收多个客户端是第一个要解决的问题，异步接收需要用到acceptor::async_accept,它接收一个socket和一个完成事件的回调函数。前面的问题3中提到监听的这个socket不能是临时变量，我们要把它保存起来，最好是统一管理起来。可以考虑用一个map去管理它们，每次一个新连接过来时，服务器自动分配一个连接号给这个连接，以方便管理。然而，socket是不允许拷贝的，所以不能直接将socket放入容器中，还需要外面包装一层才可以。

　　第二个问题是打印来自客户端的数据，既然要打印就需要异步读数据了。异步读是由socket完成，这个socket还要完成读写功能，为了简化用户操作，我将socket封装到一个读写事件处理器中，这个事件处理器只具备具备读和写的功能。服务器每次监听的时候我都会创建一个新的事件处理器并放到一个map中，客户端成功连接后就由这个事件处理器去处理各种读写事件了。 根据问题1，异步读写时要保证数据的有效性，这里我将一个固定大小的缓冲区作为读缓冲区。为了简单起见我使用同步发送，异步接收。

具体看看这个读写事件处理器是怎么写的：
```cpp
const int MAX_IP_PACK_SIZE = 65536;
const int HEAD_LEN = 4;
class RWHandler
{
public:

    RWHandler(io_service& ios) : m_sock(ios)
    {
    }

    ~RWHandler()
    {
    }

    void HandleRead()
    {
        //三种情况下会返回：1.缓冲区满；2.transfer_at_least为真(收到特定数量字节即返回)；3.有错误发生
        async_read(m_sock, buffer(m_buff), transfer_at_least(HEAD_LEN), [this](const boost::system::error_code& ec, size_t size)
        {
            if (ec != nullptr)
            {
                HandleError(ec);
                return;
            }

            cout << m_buff.data() + HEAD_LEN << endl;

            HandleRead();
        });
    }

    void HandleWrite(char* data, int len)
    {
        boost::system::error_code ec;
        write(m_sock, buffer(data, len), ec);
        if (ec != nullptr)
            HandleError(ec);
    }

    tcp::socket& GetSocket()
    {
        return m_sock;
    }

    void CloseSocket()
    {
        boost::system::error_code ec;
        m_sock.shutdown(tcp::socket::shutdown_send, ec);
        m_sock.close(ec);
    }

    void SetConnId(int connId)
    {
        m_connId = connId;
    }

    int GetConnId() const
    {
        return m_connId;
    }

    template<typename F>
    void SetCallBackError(F f)
    {
        m_callbackError = f;
    }

private:
    void HandleError(const boost::system::error_code& ec)
    {
        CloseSocket(); 
        cout << ec.message() << endl;
        if (m_callbackError)
            m_callbackError(m_connId);
    }

private:
    tcp::socket m_sock;
    std::array<char, MAX_IP_PACK_SIZE> m_buff; 
    int m_connId;
    std::function<void(int)> m_callbackError;
};
```
这个读写事件处理器有四个成员变量，第一个是socket它是具体的读写执行者；第二个是固定长度的读缓冲区，用来读数据；第三个是连接id，由连接管理层分配；第四个是回调函数，读写发生错误时回调到上层。当然还可以加一个tcp分包之后的回调函数，将应用层数据回调到应用层，这里简单起见，只是将其打印出来。

 

再来看看Server是如何写的：
```cpp
#include <boost/asio/buffer.hpp>
#include <boost/unordered_map.hpp>
#include "Message.hpp"
#include "RWHandler.hpp"

const int MaxConnectionNum = 65536;
const int MaxRecvSize = 65536;
class Server
{
public:

    Server(io_service& ios, short port) : m_ios(ios), m_acceptor(ios, tcp::endpoint(tcp::v4(), port)), m_cnnIdPool(MaxConnectionNum)
    {
        int current = 0;
        std::generate_n(m_cnnIdPool.begin(), MaxConnectionNum, [&current]{return ++current; });
    }

    ~Server()
    {
    }

    void Accept()
    {
        cout << "Start Listening " << endl;
        std::shared_ptr<RWHandler> handler = CreateHandler();

        m_acceptor.async_accept(handler->GetSocket(), [this, handler](const boost::system::error_code& error)
        {
            if (error)
            {
                cout << error.value() << " " << error.message() << endl;
                HandleAcpError(handler, error);
            }
            
            m_handlers.insert(std::make_pair(handler->GetConnId(), handler));
            cout << "current connect count: " << m_handlers.size() << endl;

            handler->HandleRead();
            Accept();
        });
    }

private:
    void HandleAcpError(std::shared_ptr <RWHandler> eventHanlder, const boost::system::error_code& error)
    {
        cout << "Error，error reason：" << error.value() << error.message() << endl;
        //关闭socket，移除读事件处理器
        eventHanlder->CloseSocket();
        StopAccept();
    }

    void StopAccept()
    {
        boost::system::error_code ec;
        m_acceptor.cancel(ec);
        m_acceptor.close(ec);
        m_ios.stop();
    }

    std::shared_ptr<RWHandler> CreateHandler()
    {
        int connId = m_cnnIdPool.front();
        m_cnnIdPool.pop_front();
        std::shared_ptr<RWHandler> handler = std::make_shared<RWHandler>(m_ios);

        handler->SetConnId(connId);

        handler->SetCallBackError([this](int connId)
        {        
            RecyclConnid(connId);
        });

        return handler;
    }

    void RecyclConnid(int connId)
    {
        auto it = m_handlers.find(connId);
        if (it != m_handlers.end())
            m_handlers.erase(it);
        cout << "current connect count: " << m_handlers.size() << endl; 
        m_cnnIdPool.push_back(connId);
    }

private:
    io_service& m_ios;
    tcp::acceptor m_acceptor;    boost::unordered_map<int, std::shared_ptr<RWHandler>> m_handlers;

    list<int> m_cnnIdPool;
};
```
这个Server具备连接管理功能，会统一管理所有连上来的客户端。 其中的Message类是boost官网中的那个[char_message](https://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/example/cpp11/chat/)
```cpp
class Message
{
public:
    enum { header_length = 4 };
    enum { max_body_length = 512 };

    Message()
        : body_length_(0)
    {
    }

    const char* data() const
    {
        return data_;
    }

    char* data()
    {
        return data_;
    }

    size_t length() const
    {
        return header_length + body_length_;
    }

    const char* body() const
    {
        return data_ + header_length;
    }

    char* body()
    {
        return data_ + header_length;
    }

    size_t body_length() const
    {
        return body_length_;
    }

    void body_length(size_t new_length)
    {
        body_length_ = new_length;
        if (body_length_ > max_body_length)
            body_length_ = max_body_length;
    }

    bool decode_header()
    {
        char header[header_length + 1] = "";
        std::strncat(header, data_, header_length);
        body_length_ = std::atoi(header);
        if (body_length_ > max_body_length)
        {
            body_length_ = 0;
            return false;
        }
        return true;
    }

    void encode_header()
    {
        char header[header_length + 1] = "";
        std::sprintf(header, "%4d", body_length_);
        std::memcpy(data_, header, header_length);
    }

private:
    char data_[header_length + max_body_length];
    std::size_t body_length_;
};
```
至此一个简单的服务端程序写完了，还要把这个Server运行起来。
```cpp
void TestServer()
{
    io_service ios;
    //boost::asio::io_service::work work(ios);
    //std::thread thd([&ios]{ios.run(); }); 

    Server server(ios, 9900);
    server.Accept();
    ios.run();

    //thd.join();
}
```
注意看这个TestServer函数，看我是如何保证io_service::run一直运行的, 我这里没有使用io_service::work来保证，用了一种更简单的方法，具体方法读者看代码便知。

现在可以写一个简单的客户端来测试一下，看看服务器能否正常工作，下一篇再继续写如何写一个简单的客户端程序。

如果你觉得这篇文章对你有用，可以点一下推荐，谢谢。

c++11 boost技术交流群：296561497，欢迎大家来交流技术。

 

一点梦想：尽自己一份力，让c++的世界变得更美好！
