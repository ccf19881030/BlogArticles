## boost显示本地和远程的IP地址、端口号
```cpp
#include <boost/asio.hpp> 
using boost::asio::ip::tcp;

boost::asio::ip::tcp::socket sock;		// 套接字

//获得本地IP
std::string localIp =  sock.local_endpoint().address().to_string();
//获得本地端口号
 unsigned short localPort = sock.local_endpoint().port();

//获得远程IP
std::string remopteIp = sock.remote_endpoint().address().to_string();
//获得本地端口号
 unsigned short remotePort = sock.remote_endpoint().port();
```
