## [boost read_some函数历程](https://yq.aliyun.com/articles/506174?spm=a2c4e.11153940.blogcont317463.21.2a7c7fb5OqsdsJ)
read_some一旦有遇到数据发送过来，就会立刻返回，但是怎么知道数据是否已经发送结束

目前的情况下，是继续等待接收，直到遇到协商的结束符号.如果read_some返回数据是0，代表对端已经关闭了
```cpp
void ReadSomeFunc()

		{

			boost::system::error_code ec;

			do

			{

				char szRecvBuf[10240] = { 0 };

				int nReadLen = m_socket.read_some(boost::asio::buffer(szRecvBuf), ec);

				if (0 == nReadLen)

				{

					char szRecvBufLeft[10240] = { 0 };

					nReadLen = m_socket.read_some(boost::asio::buffer(szRecvBufLeft), ec);

					if (0 == nReadLen) return;



					m_strMatch = m_strMatch + szRecvBufLeft;

				}

				if (ec) return;



				m_strMatch = szRecvBuf;

				int nIndexOfContentLength = m_strMatch.find("Content-Length:", 0);

				int indexOfEnd = m_strMatch.find("\r\n\r\n", 0);

				if (nIndexOfContentLength == -1) break;



				if (-1 == indexOfEnd) break;



				std::string strContextLen = m_strMatch.substr(nIndexOfContentLength + 15, indexOfEnd - nIndexOfContentLength - 15);

				unsigned int nContextLen = atoi(strContextLen.c_str());

				if (nContextLen > m_strMatch.length())

				{

					char szRecvBufLeft[40960] = { 0 };

					m_socket.read_some(boost::asio::buffer(szRecvBufLeft), ec);

					m_strMatch = m_strMatch + szRecvBufLeft;

				}



				boost::asio::streambuf request;

				std::ostream request_stream(&request);

				request_stream << "HTTP/1.1 200 OK\r\n";

				request_stream << "\r\n";

				boost::asio::write(m_socket, request, ec);

			} while (0);

		}
    ```
    1)boost asio 接收数据异常 $/x1

说明

    在发送PLAY指令之后，接收到的数据是$/x1,实际上通过调试服务器端，发现服务器端实际上已经了200 OK过来，因此猜测是接收超时，但是在前面的指令收发都没有问题，尝试在PLAY指令发送之后，接收之前调用Sleep函数睡眠500ms，没有任何的效果，查看如何设置socket超时，也没有相关资料，使用的都是同步的收发

测试代码如下：
```cpp
#include <iostream>

#include <fstream>

#include <string>

#include <sstream>

#include <boost/asio.hpp>





using namespace std;

using namespace boost::asio;



const char pszRtspServerIP[32] = "192.168.1.140";

short sRtspServerPort = 554;

std::string strFileName = "/smoke.264";

std::string strSessionId;



void WriteFile(char* buf)

{

ofstream ofs;

ofs.open("rtspoption.txt");

ofs << buf << endl;

ofs.close();

}



int ExtractSessionId(const char* pBuffer, int nStartSearchPos = 0)

{

std::string strContext = pBuffer;

const char* pszSession = "Session: ";

int nSessionStringLen = strlen(pszSession);

int nIndexSession = strContext.find(pszSession, nStartSearchPos);

if (-1 == nIndexSession) return -1;



int nIndexSemicolonAfterSession = strContext.find(";", nIndexSession);

if (-1 == nIndexSemicolonAfterSession) return -1;



strSessionId = strContext.substr(nIndexSession + nSessionStringLen, nIndexSemicolonAfterSession - nIndexSession - nSessionStringLen);

return nIndexSemicolonAfterSession;

}





int HandleOptionCommand(ip::tcp::socket &sock)

{

boost::system::error_code ec;

boost::asio::streambuf request;

std::ostream request_stream(&request);

request_stream << "OPTIONS " << "rtsp://" << pszRtspServerIP << " RTSP/1.0\r\n";

request_stream << "CSeq: " << "2\r\n";

request_stream << "User-Agent: " << "LibVLC/2.1.5 (Live555 Streaming Media v2014.0)\r\n\r\n";



boost::asio::write(sock, request);



char buf[1024] = { 0 };

size_t len = sock.read_some(buffer(buf), ec);

return 0;

}



int HanleDescribeCommand(ip::tcp::socket &sock)

{

boost::system::error_code ec;

boost::asio::streambuf request;

std::ostream request_stream(&request);

request_stream << "DESCRIBE " << "rtsp://" << pszRtspServerIP << strFileName << " RTSP/1.0\r\n";

request_stream << "CSeq: " << "3\r\n";

request_stream << "Accept: " << "application/sdp\r\n";

request_stream << "User-Agent: " << "LibVLC/2.1.5 (Live555 Streaming Media v2014.0)\r\n\r\n";



boost::asio::write(sock, request);



char buf[1024] = { 0 };

size_t len = sock.read_some(buffer(buf), ec);

return 0;

}



int HandleSetupCommand(ip::tcp::socket &sock)

{

boost::system::error_code ec;

boost::asio::streambuf request;

std::ostream request_stream(&request);

request_stream << "SETUP " << "rtsp://" << pszRtspServerIP << strFileName << " RTSP/1.0\r\n";

request_stream << "CSeq: " << "4\r\n";

request_stream << "Transport: " << "RTP/AVP/TCP;unicast;interleaved=0-1\r\n";

request_stream << "User-Agent: " << "LibVLC/2.1.5 (Live555 Streaming Media v2014.0)\r\n\r\n";



boost::asio::write(sock, request);



char buf[1024] = { 0 };

int id = 0;

size_t len = sock.read_some(buffer(buf), ec);

ExtractSessionId(buf);

return 0;



}



int HanlePlayCommand(ip::tcp::socket &sock)

{

boost::system::error_code ec;

boost::asio::streambuf request;

std::ostream request_stream(&request);

request_stream << "PLAY " << "rtsp://" << pszRtspServerIP << strFileName << " RTSP/1.0\r\n";

request_stream << "CSeq: " << "5\r\n";

request_stream << "Session: " << strSessionId << "\r\n";

request_stream << "Range: " << "npt=0.000-\r\n";

request_stream << "User-Agent: " << "LibVLC/2.1.5 (Live555 Streaming Media v2014.0)\r\n\r\n";



boost::asio::write(sock, request);



char buf[1024] = { 0 };

int id = 0;

::Sleep(500);

size_t len = sock.read_some(buffer(buf), ec);

return 0;

}



int main(int argc, char* argv[])

{

io_service iosev;

ip::tcp::socket socket(iosev);

ip::tcp::endpoint ep(ip::address_v4::from_string(pszRtspServerIP), sRtspServerPort);

boost::system::error_code ec;

socket.connect(ep, ec);

if (ec) return -1;



HandleOptionCommand(socket);

HanleDescribeCommand(socket);

HandleSetupCommand(socket);

HanlePlayCommand(socket);



return 0;

}
```
#### [原文链接：http://blog.51cto.com/fengyuzaitu/1952457](http://blog.51cto.com/fengyuzaitu/1952457)

    
