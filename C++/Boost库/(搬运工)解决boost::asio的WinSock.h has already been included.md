## [(搬运工)解决boost::asio的WinSock.h has already been included](http://www.cppblog.com/ming81/archive/2013/02/17/197875.html)
开始使用boost::asio库时，编译碰到这个错误提示：

fatal error C1189: #error :  WinSock.h has already been included

查了下抛出这个错误的boost代码，原来是定义了_WINSOCKAPI_，但没有定义_WINSOCK2API_

那哪里定义了_WINSOCKAPI_呢？

后来在网上查了下，原来是我包含了Windows.h头文件，而Windows.h头文件又包含了WinSock.h这个老东西

 

知道原因就简单了，试了下，方法有三种可解决此错误：

1、在包含Windows.h前定义宏WIN32_LEAN_AND_MEAN，就OK了（WIN32_LEAN_AND_MEAN表示不包含一些极少使用和偏门的资料）

2、在包含Windows.h前包含winsock2.h

3、在包含Windows.h前包含asio.hpp
