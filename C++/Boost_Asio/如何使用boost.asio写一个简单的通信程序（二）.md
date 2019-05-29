## [如何使用boost.asio写一个简单的通信程序（二）](https://www.cnblogs.com/qicosmos/p/3471314.html) 
先说下[上一篇文章]()中提到的保持io_service::run不退出的简单办法。因为只要异步事件队列中有事件，io_service::run就会一直阻塞不退出，所以只要保证异步事件队列中一直有事件就行了，如何让异步事件队列中一直有事件呢？一个简单的办法就是循环发起异步读操作，如果对方一直都不发数据过来，则这个异步读事件就会一直在异步事件队列中，这样io_service::run就不会退出了。但是这样有一个缺点就是io_service::run处于阻塞会阻塞当前线程，如果不希望阻塞当前线程，就还是通过work来保持io_service::run不退出。

　　现在言归正传，看看如何用asio写一个简单的客户端。我希望这个客户端具备读写能力，还能自动重连。我希望用一个连接器类去实现连接以及IO事件的处理，连接器具体的职责有三个：1.连接到服务器；2.重连。3.通过事件处理器实现读写。其中，实现重连可以用一个专门的线程去检测，为了简单，不设置重连次数，保持一直重连。实现读写可以直接用上篇中的RWHandler。看看连接器Connctor是如何写的：
  ```cpp
  class Connector
{
public:

    Connector(io_service& ios, const string& strIP, short port) :m_ios(ios), m_socket(ios),
        m_serverAddr(tcp::endpoint(address::from_string(strIP), port)), m_isConnected(false), m_chkThread(nullptr)
    {
        CreateEventHandler(ios);
    }

    ~Connector()
    {
    }

    bool Start()
    {        
        m_eventHandler->GetSocket().async_connect(m_serverAddr, [this](const boost::system::error_code& error)
        {
            if (error)
            {
                HandleConnectError(error);
                return;
            }
            cout << "connect ok" << endl;
            m_isConnected = true;
            m_eventHandler->HandleRead(); //连接成功后发起一个异步读的操作
        });

        boost::this_thread::sleep(boost::posix_time::seconds(1));
        return m_isConnected;
    }

    bool IsConnected() const
    {
        return m_isConnected;
    }

    void Send(char* data, int len)
    {
        if (!m_isConnected)
            return;

        m_eventHandler->HandleWrite(data, len);
    }

    void AsyncSend(char* data, int len)
    {
        if (!m_isConnected)
            return;

        m_eventHandler->HandleAsyncWrite(data, len);
    }

private:
    void CreateEventHandler(io_service& ios)
    {
        m_eventHandler = std::make_shared<RWHandler>(ios);
        m_eventHandler->SetCallBackError([this](int connid){HandleRWError(connid); });
    }

    void CheckConnect()
    {
        if (m_chkThread != nullptr)
            return;

        m_chkThread = std::make_shared<std::thread>([this]
        {
            while (true)
            {
                if (!IsConnected())
                    Start();

                boost::this_thread::sleep(boost::posix_time::seconds(1));
            }
        });
    }

    void HandleConnectError(const boost::system::error_code& error)
    {
        m_isConnected = false;
        cout << error.message() << endl;
        m_eventHandler->CloseSocket();
        CheckConnect();
    }

    void HandleRWError(int connid)
    {
        m_isConnected = false;
        CheckConnect();
    }

private:
    io_service& m_ios;
    tcp::socket m_socket;

    tcp::endpoint m_serverAddr; //服务器地址

    std::shared_ptr<RWHandler> m_eventHandler;
    bool m_isConnected;
    std::shared_ptr<std::thread> m_chkThread; //专门检测重连的线程
};
```
注意看连接成功之后，我发起了一个异步读操作，它的作用除了接收数据之外，还可以用来判断连接是否断开，因为当连接断开时，异步接收事件会触发，据此可以做重连操作。可以看到，在连接失败后，或者读写发生错误之后我会关闭连接然后开始自动重连。

　　再看看测试代码：
 ```cpp
 int main()
{
    io_service ios;
    boost::asio::io_service::work work(ios);
    boost::thread thd([&ios]{ios.run(); });

    Connector conn(ios, "127.0.0.1", 9900);
    conn.Start();

    if (!conn.IsConnected())
    {
        Pause();
        return -1;
    }
    
    const int len = 512;
    char buf[len] = "";
    
    while (std::cin.getline(line, sizeof(line)))
    {
        conn.Send(line, sizeof(line));
    }    

    return 0;
}
```
注意看我是通过work和一个专门的线程的线程去run保持io_service不退出的。 至此，一个简单的客户端完成了。 不过，我并没有提到如何异步发送，异步发送稍微麻烦一点，它涉及发送队列以及如何异步循环发送的问题，为了简单起见就没有专门去讲它，也许后面会用专门的篇幅去讲异步发送。一般情况下同步发送足够了，如果希望更高的发送效率，可以考虑半同步半异步的线程池去发送，以提高效率。
  
