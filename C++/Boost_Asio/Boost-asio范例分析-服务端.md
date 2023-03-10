## [Boost::asio范例分析 服务端](https://www.2cto.com/kf/201304/201605.html)
## [Boost::asio范例分析 客户端](https://www.2cto.com/kf/201304/201606.html)

### Boost::asio范例分析 服务端
main函数要求程序调用者传递3个参数:服务器IP地址,端口号和文档根目录.其中IP地址可以是IPv4或IPv6格式.接着创建server对象实例,将传递进来的IP地址,端口号,文档根目录作为server对象的构造函数参数传递到处理程序中.最后调用server的run成员函数启动服务端处理例程.
    http::server::server s(argv[1], argv[2], argv[3]);
  s.run();
  首先看看server类的定义和实现.为防止server对象被拷贝复制,这个类从boost::noncopyable类私有继承.这个类主要用来控制服务端核心代码的运行,管理tcp链接请求,建立链接缓冲池等功能.
  Server类定义的数据成员:
1) boost::asio::io_service io_service_;这个对象很熟悉了,用来执行异步操作.
2) boost::asio::signal_set signals_;信号集合用来注册程序结束信号,以便于退出时释放资源.
3) boost::asio::ip::tcp::acceptor acceptor_;接收器用来侦听到来的链接请求.
4) connection_manager connection_manager_;连接池用来管理所有活动的链接.
5) connection_ptr new_connection_;这是一个shared_ptr类型,用来存放新建的链接,是实现链接自动释放的关键.
6) request_handler request_handler_;请求处理器,用来处理所有到来的请求.
  Server类的函数成员:
1) 构造函数:构造函数初始化了上述的数据成员,并向signals_信号集合中添加程序发生中断和结束的信号,并在信号集合上设置异步等待,当集合中的信号受信后执行server::handle_stop函数,结束当前运行的链接对象.接着根据传入的服务器地址参数得到端点,与接收器绑定开始侦听客户端的链接,并执行start_accept函数成员,处理到来的链接请求.
server::server(const std::string& address, const std::string& port,
    const std::string& doc_root)
  : io_service_(),
    signals_(io_service_),
    acceptor_(io_service_),
    connection_manager_(),
    new_connection_(),
    request_handler_(doc_root)
{
  signals_.add(SIGINT);
  signals_.add(SIGTERM);
#if defined(SIGQUIT)
  signals_.add(SIGQUIT);
#endif // defined(SIGQUIT)
  signals_.async_wait(boost::bind(&server::handle_stop, this));

  boost::asio::ip::tcp::resolver resolver(io_service_);
  boost::asio::ip::tcp::resolver::query query(address, port);
  boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
  acceptor_.open(endpoint.protocol());
  acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  acceptor_.bind(endpoint);
  acceptor_.listen();

  start_accept();
}
2) Server::run函数:
这个函数实现比较简单,调用io_service_.run();函数启动异步操作.
3) Server::start_accept函数:
这个函数首先创建一个新的链接对象,并使用new_connection_对象来保证自动释放(引用计数减一).通过shared_ptr类的reset成员函数,使new_connection_释放掉原来持有的链接对象,转而管理新建的链接.接着启动异步接收操作,收到异步链接后,执行server::handle_accept函数.注意connection类的构造函数接收一个链接池对象,创建好链接后自动将链接放入缓冲池进行管理.
void server::start_accept()
{
  new_connection_.reset(new connection(io_service_,
        connection_manager_, request_handler_));
  acceptor_.async_accept(new_connection_->socket(),
      boost::bind(&server::handle_accept, this,
        boost::asio::placeholders::error));
}
4) server::handle_accept函数:
这个函数启动链接对象的处理流程,并调用start_accept继续接收到来的客户端链接.这个函数与start_accept函数构成了递归调用,异步接收到链接后进行处理并再次启动异步链接.
void server::handle_accept(const boost::system::error_code& e)
{
  if (!acceptor_.is_open())
  {
    return;
  }
  if (!e)
  {
    connection_manager_.start(new_connection_);
  }
  start_accept();
}
5) server::handle_stop函数:
这个函数由信号集合受信后异步除法,用来停止接收器,停止当前链接处理例程.
void server::handle_stop()
{
  acceptor_.close();
  connection_manager_.stop_all();
}
接下来分析一下connection类.这个类从enable_shared_from_this<connection>类和noncopyable类继承,前一个父类提供了shared_from_this()成员函数,返回持有this指针的shared_ptr对象,实现了自动内存回收.后一个基类防止对象被拷贝复制.这个类的实现与asio的echo服务端范例很相似,只增加了解析http协议包的对象成员和连接池成员.
Connection类的数据成员:
1) boost::asio::ip::tcp::socket socket_;链接的socket对象,用来进行与客户端通信.
2) connection_manager& connection_manager_;连接池对象
3) request_handler& request_handler_;请求处理对象
4) boost::array<char, 8192> buffer_;接收客户端数据的缓冲区
5) request request_;请求对象
6) request_parser request_parser_;请求解析对象
7) reply reply_;应答对象
   Connection类的函数成员:
1) 构造函数:
这里只是初始化了上述的数据成员.
connection::connection(boost::asio::io_service& io_service,
    connection_manager& manager, request_handler& handler)
  : socket_(io_service),
    connection_manager_(manager),
    request_handler_(handler)
{
}
2) connection::socket函数:
简单的返回链接的socket对象.
3) Connection::start函数:
这个函数启动异步接收客户端数据操作.接收到数据存入数据成员buffer_中后调用handle_read函数进行处理.注意async_read_some接收数据后马上返回,不会判断接收到的数据大小.如果使用全局async_read函数则必须在缓冲区被填满后才返回.
void connection::start()
{
  socket_.async_read_some(boost::asio::buffer(buffer_),
      boost::bind(&connection::handle_read, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}
4) Connection::stop函数:
函数简单的调用socket_close()停止socket对象.
5) Connection::handle_read函数:
这个函数处理connection对象的核心逻辑,接收到数据后,处理http请求,解析成功则根据请求组织响应信息发送给客户端.如果解析失败则向客户端发送错误信息.
void connection::handle_read(const boost::system::error_code& e,
    std::size_t bytes_transferred)
{
  if (!e)//接收时没有发生错误
  {
boost::tribool result;//三状态bool类型
// boost::tie构造一个类似pair的对象,用来接收函数的多个返回值
//这里解析接收到http请求,并将解析结果存入request_结构体中.
    boost::tie(result, boost::tuples::ignore) = request_parser_.parse(
        request_, buffer_.data(), buffer_.data() + bytes_transferred);
    if (result)//如果解析成功
    {
      request_handler_.handle_request(request_, reply_);//处理请求,生成响应数据
      boost::asio::async_write(socket_, reply_.to_buffers(),//发送响应数据
          boost::bind(&connection::handle_write, shared_from_this(),
            boost::asio::placeholders::error));
    }
    else if (!result)//解析失败,则想客户端发送错误信息
    {
      reply_ = reply::stock_reply(reply::bad_request);
      boost::asio::async_write(socket_, reply_.to_buffers(),
          boost::bind(&connection::handle_write, shared_from_this(),
            boost::asio::placeholders::error));
    }
    else//解析结果为第三状态,则继续接收
    {
      socket_.async_read_some(boost::asio::buffer(buffer_),
          boost::bind(&connection::handle_read, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
  }
  else if (e != boost::asio::error::operation_aborted)
  {
    connection_manager_.stop(shared_from_this());
  }
}
6) Connection::handle_write函数:
向客户端异步发送响应数据后,调用这个函数,关闭socket链接,结束一次HTTP请求.并从连接池中将这个链接清除掉,回收这个链接对象的内存空间.
void connection::handle_write(const boost::system::error_code& e)
{
  if (!e)//如果发送响应数据成功
  {
boost::system::error_code ignored_ec;
// shutdown停止socket发送接收函数,但不释放socket对象
    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
  }
  if (e != boost::asio::error::operation_aborted)
  {
    connection_manager_.stop(shared_from_this());
  }
}
  这里说说connection的内存管理机制,接收到客户端链接请求后,使用一个shared_ptr对象持有一个新建的链接对象,当这个shared_ptr转而持有其他对象时,将对此链接对象的引用计数减一.而connection类中的异步处理函数中传递的this指针都是通过share_from_this获取的,这个传递的this指针也是被shared_ptr对象进行管理的,处理完毕后引用计数自动减一.当与这个链接相关的所有操作都执行完毕后,链接对象的引用计数为0,自动释放.由此实现了每个客户端链接创建一个链接对象,链接对象处理完请求后释放自己.
  再看连接池类的实现. connection_manager类从noncopyable继承,防止拷贝复制.
connection_manager的数据成员:
1) std::set<connection_ptr> connections_;定义一个存放链接对象的集合.
connection_manager的函数成员:
1) connection_manager::start函数:
这个函数有一个connection_ptr类型的参数,函数将这个链接存入connections_集合,并调用这个链接的start函数,启动链接的处理操作.
2) connection_manager::stop函数:
这个函数有一个connection_ptr类型的参数,将链接从connections_集合中去除,并调用链接的stop函数停止请求处理.
3) connection_manager::stop_all函数:
对connections_集合中的每个链接都调用其stop方法,并清空集合.
void connection_manager::stop_all()
{
  //for_each表示对从起始迭代器至终止迭代器的每个对象都执行第三个参数指定的函数操作,
//_1 用于替换当前迭代器执行的对象,是一个占位符
  std::for_each(connections_.begin(), connections_.end(),
      boost::bind(&connection::stop, _1));
  connections_.clear();
}
稍后研究请求解析类,请求处理类和响应类的代码.

下面看看请求解析器request_parser.这个类主要的作用就是解析http请求,从中提取出http请求中方法,uri,指定的http版本号,请求头等信息.这个类的成员函数parse定义如下:

  template <typename InputIterator>
  boost::tuple<boost::tribool, InputIterator> parse(request& req,
      InputIterator begin,  InputIterator end)
  {
    while (begin != end)
    {
      boost::tribool result = consume(req, *begin++);
      if (result || !result)
        return boost::make_tuple(result, begin);
    }
    boost::tribool result = boost::indeterminate;
    return boost::make_tuple(result, begin);
  }

三个参数分别为返回分析出来http请求信息的request结构体,和起始迭代器及截止迭代器.函数对迭代器对指定的每个字符调用consume方法,如果返回true或false则结束循环,否则继续.consume函数分析传入的char参数,根据商定的协议和当前状态state_解析这个char字符,将char字符加入到request结构体的成员中或调整当前状态state_.如果一个request成员没有解析完则返回boost::indeterminate,指示继续传递下一个字符.解析出错和完成返回true或false.这种协议解析方式很清晰,很多地方可以借鉴.当然如果协议调整了,对应的解析代码也需要相应变动.

request_handler类负责处理http请求.这个类从noncopyable类继承,防止拷贝复制,构造函数接受一个string参数指定根目录.在解析完http请求后,将得到的request结构体传递给这个类的handle_request成员函数,解码request中指定的url地址(即请求文件名称),如果解码出错项客户端发送错误信息.如果只指定了文件的目录,则从指定目录中寻找index.html文件.接着使用ifstream对象打开指定的文件,将文件内容读入到数组中,并添加到响应结构体reply的content中(str::string类型).最后生成响应结构体的headers信息,指定响应的长度和类型(文件后缀).在connection类的handle_read成员函数中获取到响应信息后,异步向客户端发送响应数据.

  char buf[512];
  while (is.read(buf, sizeof(buf)).gcount() > 0)//gcount返回读取到的字节数量
    rep.content.append(buf, is.gcount());
  rep.headers.resize(2);
  rep.headers[0].name = "Content-Length";
  rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
  rep.headers[1].name = "Content-Type";
  rep.headers[1].value = mime_types::extension_to_type(extension);

这个服务端范例没有提供多线程支持,在http的server2范例中提供了线程池支持,以后有机会继续分析.

### Boost::asio范例分析 客户端
为了方便描述,这里只分析一下同步实现,异步实现方式和同步方式的流程是一致的,只是在函数调用的方式上有些区别.分析清楚了同步方式,在看异步实现,也很容易.

  这个HTTP范例实现了客户端向服务端请求文件内容的功能,客户端给出一个文件名称,服务端在本地寻找文件,并将文件内容(文本文件)返回给客户端.

  main函数首先检查传递给exe执行文件的参数,第一个参数是服务端的IP地址,第二个参数是请求的文件名称,如果仅指定了目录而没有具体的文件名,则在这个目录中查找index.htm文件.

    //定义io_service对象实例,任何使用asio的程序中都要进行定义,是asio库的核心实现.

    boost::asio::io_service io_service;

    //argv[1]是服务端IP地址,由程序调用方提供,

    //在指定服务器上寻找http服务,并获取网络端点

    tcp::resolver resolver(io_service);

    tcp::resolver::query query(argv[1], "http");

    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    // 尝试获取到的每个端点,直到建立了一个有效的链接.

    tcp::socket socket(io_service);

    boost::asio::connect(socket, endpoint_iterator);

  至此,链接建立成功.接下来就是向服务端发送和接受数据了.

    //建立一个流缓冲区,用来存储发送和接受的数据

    boost::asio::streambuf request;

    //将流缓冲区与一个输出流ostream绑定,对ostream的输出操作最终都存入到流缓冲区.

    std::ostream request_stream(&request);

    //根据客户端与服务端制定的协议,组织HTTP请求包的头信息.argv[2]指定了文件名称.

    request_stream << "GET " << argv[2] << " HTTP/1.0\r\n";

    request_stream << "Host: " << argv[1] << "\r\n";

    request_stream << "Accept: */*\r\n";

    request_stream << "Connection: close\r\n\r\n";

    //向服务端发送HTTP请求

    boost::asio::write(socket, request);

  这时HTTP服务端接受到客户端发送的请求后,按双边协议对请求信息进行解析,获取到文件名称和HTTP协议的版本号,并进行相应的处理,将HTTP响应状态信息,包头信息和文件内容发送给客户端.客户端接收这些信息,并进行检查处理.

  接收响应的状态信息:

    //定义接收响应数据的流缓冲区

    boost::asio::streambuf response;

    //从服务端接收响应包的头信息,描述响应的状态

    //流缓冲区可根据接收的数据自动调节大小,可在其构造函数中指定最大流缓冲区.

    boost::asio::read_until(socket, response, "\r\n");

  检查响应包的状态:

    //将流缓冲区与istream相关联,可方便的从流缓冲区中提取出信息

    std::istream response_stream(&response);

    std::string http_version;

    //获取http版本号

    response_stream >> http_version;

    unsigned int status_code;

    //获取响应信息的状态码

    response_stream >> status_code;

    std::string status_message;

    //获取状态信息

    std::getline(response_stream, status_message);

    //检查包是否为HTTP请求的响应包

    if (!response_stream || http_version.substr(0, 5) != "HTTP/")

    {

      std::cout << "Invalid response\n";

      return 1;

    }

    if (status_code != 200)//状态码为200表示请求成功,否则失败

    {

      std::cout << "Response returned with status code " << status_code << "\n";

      return 1;

    }

  如果检查通过,则开始接收响应包的包头.

    boost::asio::read_until(socket, response, "\r\n\r\n");

    //处理响应包头信息

    std::string header;

    while (std::getline(response_stream, header) && header != "\r")

      std::cout << header << "\n";

    std::cout << "\n";

    // 打印出所有输出的信息

    if (response.size() > 0)  std::cout << &response;

  现在开始接收文件内容,直到遇到了EOF符号,并将接收到的数据直接输出

    boost::system::error_code error;

    //read函数返回接收到的字节数,这里用了while循环,表示一直接收,直到接收不到为止.

    // transfer_at_least 函数返回transfer_at_least_t类型,

    //这是一个函数对象,会将接收到的数据字节数与其参数相比较,

    //如果大于等于指定数量则返回,这里指定为1表示接收到数据就返回处理.

    while (boost::asio::read(socket, response,

          boost::asio::transfer_at_least(1), error))

      std::cout << &response;//直接将接收到的数据进行显示

    if (error != boost::asio::error::eof)

      throw boost::system::system_error(error);
