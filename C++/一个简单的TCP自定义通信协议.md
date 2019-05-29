# [一个简单的TCP自定义通信协议](https://blog.csdn.net/fengxinlinux/article/details/72888759)
## 我们为什么要自定义TCP应用层传输协议？
因为在TCP流传输的过程中，可能会出现分包与黏包的现象。我们为了解决这些问题，需要我们自定义通信协议进行封包与解包。
### 什么是分包与黏包？
分包：指接收没有接受到一个完整的包，只接收了部分。
黏包：指发送方发送的若干包数据到接收方接收时粘成一包，从接收缓冲区看，后一包数据的头紧接着前一包数据的尾。
PS:因为TCP是面向字节流的，是没有边界的概念的，严格意义上来说，是没有分包和黏包的概念的，但是为了更好理解，也更好来描述现象，我在这里就接着采用这两个名词来解释现象了。我觉得大家知道这个概念就行了，不必细扣，能解决问题就行。
## 产生分包与黏包现象的原因是什么？
### 产生分包原因：
可能是IP分片传输导致的，也可能是传输过程中丢失部分包导致出现的半包，还有可能就是一个包可能被分成了两次传输，在取数据的时候，先取到了一部分（还可能与接收的缓冲区大小有关系），总之就是一个数据包被分成了多次接收。
### 产生黏包的原因：
由于TCP协议本身的机制（面向连接的可靠地协议-三次握手机制）客户端与服务器会维持一个连接（Channel），数据在连接不断开的情况下，可以持续不断地将多个数据包发往服务器，但是如果发送的网络数据包太小，那么他本身会启用Nagle算法（可配置是否启用）对较小的数据包进行合并（基于此，TCP的网络延迟要UDP的高些）然后再发送（超时或者包大小足够）。那么这样的话，服务器在接收到消息（数据流）的时候就无法区分哪些数据包是客户端自己分开发送的，这样产生了粘包；服务器在接收到数据后，放到缓冲区中，如果消息没有被及时从缓存区取走，下次在取数据的时候可能就会出现一次取出多个数据包的情况，造成粘包现象
### 什么是封包与解包？
TCP/IP 网络数据以流的方式传输，数据流是由包组成，如何判定接收方收到的包是否是一个完整的包就要在发送时对包进行处理，这就是封包技术，将包处理成包头，包体。
包头是包的开始标记，整个包的大小就是包的结束标。
## 如何自定义协议？
发送时数据包是由包头+数据 组成的：其中包头内容分为包类型+包长度。

接收时，只需要先保证将数据包的包头读完整，通过收到的数据包包头里的数据长度和数据包类型，判断出我们将要收到一个带有什么样类型的多少长度的数据。然后循环接收直到接收的数据大小等于数据长度停止，此时我们完成接收一个完整数据包。

## 代码实现:
接下来是我写的一个客户端和服务器的代码。文件的读取和创建写入，是使用的linux下的系统调用。服务器是单线程epoll。通过使用自己定义的通信协议实现客户端向服务器发送文件。代码我用c++简单的封装了一下，重点是数据包的定义，以及发送数据和接收数据时包的处理代码(protocol.h,server_recv(),send_to_serv())。
头文件protocol.h：
含有数据包类型的定义，并且我把客户端和服务器共同需要的函数与类型定义也放进去了。
```cpp
//protocol.h

#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#define NET_PACKET_DATA_SIZE 5000

/// 网络数据包包头
struct NetPacketHeader
{
    unsigned short      wDataSize;  ///< 数据包大小，包含封包头和封包数据大小
    unsigned short      wOpcode;    ///< 操作码
};

/// 网络数据包
struct NetPacket
{
    NetPacketHeader     Header;                         ///< 包头
    unsigned char       Data[NET_PACKET_DATA_SIZE];     ///< 数据
};



/// 网络操作码
enum eNetOpcode
{
    NET_TEST1  = 1,  //发送文件信息
    NET_TEST2=2     //发送文件内容
};


struct File_message
{
    char filename[100];  //文件名
    long filesize;  //文件大小
};

struct File_data
{
    char filename[100];  //文件名
    unsigned char buffer[1024]; //文件内容
};

void my_err(const char *err_string,int line)  //自定义错误函数
{
    std::cerr<<"line:"<<line<<std::endl; //输出错误发生在第几行
    perror(err_string);       //输出错误信息提示
    exit(1);
}

#endif
```
服务器代码:
```cpp
#include<iostream>
#include<cstring>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/signal.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<errno.h>

#include"protocol.h"

using namespace std;

 
#define PORT 6666   //服务器端口
#define LISTEN_SIZE 1023   //连接请求队列的最大长度
#define EPOLL_SIZE  1023   //epoll监听客户端的最大数目
  

class TCPServer
{
    public: 

    TCPServer();
    ~TCPServer();
    
     /// 接受客户端接入
    void acceptClient();

    /// 关闭客户端
    void closeClient(int i);
    //处理接收到的数据
    bool dealwithpacket(int conn_fd,unsigned char *recv_data,uint16_t wOpcode,int datasize);

    bool server_recv(int conn_fd);  //接收数据函数

    void run();  //运行函数
    
    private:

    int sock_fd;  //监听套接字
    int conn_fd;    //连接套接字
    int epollfd;  //epoll监听描述符
    socklen_t cli_len;  //记录连接套接字地址的大小
    struct epoll_event  event;   //epoll监听事件
    struct epoll_event*  events;  //epoll监听事件集合
    struct sockaddr_in cli_addr;  //客户端地址
    struct sockaddr_in serv_addr;   //服务器地址


};

TCPServer::TCPServer()  //构造函数
{

    //创建一个套接字
    sock_fd=socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd<0)
    {
        my_err("socket",__LINE__);
    }
    //设置该套接字使之可以重新绑定端口
    int optval=1;
    if(setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,(void*)&optval,sizeof(int))<0)
    {
        my_err("setsock",__LINE__);
    }
    //初始化服务器端地址结构
    memset(&serv_addr,0,sizeof(struct sockaddr_in));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    if(bind(sock_fd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr_in))<0)
    {
        my_err("bind",__LINE__);
    }
    //将套接字转化为监听套接字
    if(listen(sock_fd,LISTEN_SIZE)<0)
    {
        my_err("listen",__LINE__);
    }


    cli_len=sizeof(struct sockaddr_in);
    events=(struct epoll_event*)malloc(sizeof(struct epoll_event)*EPOLL_SIZE); //分配内存空间

    //创建一个监听描述符epoll,并将监听套接字加入监听列表
    epollfd=epoll_create(EPOLL_SIZE);
    if(epollfd==-1)
    {
        my_err("epollfd",__LINE__);
    }
    event.events = EPOLLIN;
    event.data.fd = sock_fd;
    if(epoll_ctl(epollfd,EPOLL_CTL_ADD,sock_fd,&event)<0)
    {
        my_err("epoll_ctl",__LINE__);
    }
    
}

TCPServer::~TCPServer()   //析构函数
{
    close(sock_fd);    //关闭监听套接字
    cout<<"服务器成功退出"<<endl;
}

void TCPServer::acceptClient()      //接受客户端连接请求
{
    conn_fd=accept(sock_fd,(struct sockaddr*)&cli_addr,&cli_len);
    if(conn_fd<0)
    {
        my_err("accept",__LINE__);
    }
    event.events = EPOLLIN | EPOLLRDHUP; //监听连接套接字的可读和退出
    event.data.fd = conn_fd;
    if(epoll_ctl(epollfd,EPOLL_CTL_ADD,conn_fd,&event)<0) //将新连接的套接字加入监听
    {
        my_err("epoll",__LINE__);
    }
    cout<<"a connet is connected,ip is "<<inet_ntoa(cli_addr.sin_addr)<<endl;
}


void TCPServer::closeClient(int i)     //处理客户端退出
{
    cout<<"a connet is quit,ip is "<<inet_ntoa(cli_addr.sin_addr)<<endl;
    epoll_ctl(epollfd,EPOLL_CTL_DEL,events[i].data.fd,&event);
    close(events[i].data.fd);

}

bool TCPServer::dealwithpacket(int conn_fd,unsigned char *recv_data,uint16_t wOpcode,int datasize)  //处理接收到的数据
{
    

    int fd;
    if(wOpcode==1)  //接收文件信息
    { 
        File_message *file_message=(File_message*)recv_data;
        strcat(file_message->filename,".down");
        

        if((fd=open(file_message->filename,O_RDWR|O_APPEND|O_CREAT,0777))<0)
        {
            cout<<"创建文件失败"<<endl;
            return false;
        }
    }
    else if(wOpcode==2)  //接收文件内容
    {
        
        File_data * file_data=(File_data*)recv_data;

        strcat(file_data->filename,".down");
        if((fd=open(file_data->filename,O_RDWR|O_APPEND))<0)
        {
            cout<<"打开文件失败"<<endl;
            return false;
        }
        if(write(fd,file_data->buffer,datasize-sizeof(file_data->filename))<0)
        {
            cout<<"写入文件失败"<<endl;
            return false;
        }
        close(fd);
    }
   return true;
    
}

bool TCPServer::server_recv(int conn_fd)  //接收数据函数
{
    int nrecvsize=0; //一次接收到的数据大小
    int sum_recvsize=0; //总共收到的数据大小
    int packersize;   //数据包总大小
    int datasize;     //数据总大小
    unsigned char recv_buffer[10000];  //接收数据的buffer


    memset(recv_buffer,0,sizeof(recv_buffer));  //初始化接收buffer
    

    while(sum_recvsize!=sizeof(NetPacketHeader))
    {
        nrecvsize=recv(conn_fd,recv_buffer+sum_recvsize,sizeof(NetPacketHeader)-sum_recvsize,0);
        if(nrecvsize==0)
        {
            cout<<"从客户端接收数据失败"<<endl;
            return false;
        }
        sum_recvsize+=nrecvsize;

    }
    


    NetPacketHeader *phead=(NetPacketHeader*)recv_buffer;
    packersize=phead->wDataSize;  //数据包大小
    datasize=packersize-sizeof(NetPacketHeader);     //数据总大小

    


    while(sum_recvsize!=packersize)
    {
        nrecvsize=recv(conn_fd,recv_buffer+sum_recvsize,packersize-sum_recvsize,0);
        if(nrecvsize==0)
        {
            cout<<"从客户端接收数据失败"<<endl;
            return false;
        }
        sum_recvsize+=nrecvsize;
    }

    
    dealwithpacket(conn_fd,(unsigned char*)(phead+1),phead->wOpcode,datasize);  //处理接收到的数据



}

void TCPServer::run()  //主执行函数
{
    while(1)   //循环监听事件
    {
        int sum=0,i;
        sum=epoll_wait(epollfd,events,EPOLL_SIZE,-1);
        for(i=0;i<sum;i++)
        {
            if(events[i].data.fd==sock_fd)    //客户端请求连接
            {
                acceptClient();  //处理客户端的连接请求

            }
            else if(events[i].events&EPOLLIN)    //客户端发来数据
            {
                
                server_recv(events[i].data.fd);  //接收数据包并做处理
                
            }
            if(events[i].events&EPOLLRDHUP) //客户端退出
            {
                closeClient(i);    //处理客户端退出
            }
            
        }
    }
}

int main()
{
    TCPServer server;
    server.run();

    return 0;
}
```
客户端代码:
```cpp
#include<iostream>
#include<string.h>
#include<math.h>
#include<sys/signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>

#include"protocol.h"

#define PORT 6666   //服务器端口

using namespace std;

class TCPClient
{
    public:

    TCPClient(int argc ,char** argv);
    ~TCPClient();


    //向服务器发送数据
    bool send_to_serv(unsigned char *data_buffer,int datasize,uint16_t wOpcode);
    bool send_file();   //向服务器发送文件
    void run(); //主运行函数


    private:

    int conn_fd; //创建连接套接字
    struct sockaddr_in serv_addr; //储存服务器地址

};




TCPClient::TCPClient(int argc,char **argv)  //构造函数
{
    if(argc!=3)    //检测输入参数个数是否正确
    {
        cout<<"Usage: [-a] [serv_address]"<<endl;
        exit(1);
    }


    //初始化服务器地址结构
    memset(&serv_addr,0,sizeof(struct sockaddr_in));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);

    //从命令行服务器地址
    for(int i=0;i<argc;i++)
    {
        if(strcmp("-a",argv[i])==0)
        {

            if(inet_aton(argv[i+1],&serv_addr.sin_addr)==0)
            {
                cout<<"invaild server ip address"<<endl;
                exit(1);
            }
            break;
        }
    }

    //检查是否少输入了某项参数
    if(serv_addr.sin_addr.s_addr==0)
    {
        cout<<"Usage: [-a] [serv_address]"<<endl;
        exit(1);
    }

    //创建一个TCP套接字
    conn_fd=socket(AF_INET,SOCK_STREAM,0);


    if(conn_fd<0)
    {
        my_err("connect",__LINE__);
    }

    //向服务器发送连接请求
    if(connect(conn_fd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr))<0)
    {
        my_err("connect",__LINE__);
    }
    
}

TCPClient::~TCPClient()  //析构函数
{
    close(conn_fd);

}

bool TCPClient::send_to_serv(unsigned char *data_buffer,int datasize,uint16_t wOpcode) //向服务器发送数据
{
    NetPacket send_packet;   //数据包
    send_packet.Header.wDataSize=datasize+sizeof(NetPacketHeader);  //数据包大小
    send_packet.Header.wOpcode=wOpcode;

    memcpy(send_packet.Data,data_buffer,datasize);  //数据拷贝


    if(send(conn_fd,&send_packet,send_packet.Header.wDataSize,0))
       return true;
    else
       return false;

}


bool TCPClient::send_file()   //向服务器发送文件
{
    unsigned char send_buffer[1024]; //发送数据buffer
    string filename;  //文件路径名
    int fd; //文件描述符
    struct stat file_buffer;  //文件属性buffer
    File_message file_message;   //文件信息
    File_data file_data;    //存储文件的内容和大小
    int nsize=0;     //一次读取的数据大小
    int sum_size=0;     //总共读取的数据大小



    memset(send_buffer,0,sizeof(send_buffer));

    cout<<"请输入要发送的文件路径及文件名"<<endl;
    getline(cin,filename);

    if(fd=open(filename.c_str(),O_RDONLY)<0)
    {
        my_err("open file error",__LINE__);
    }
    if(stat(filename.c_str(),&file_buffer)<0)
    {
        my_err("stat file error",__LINE__);
    }

    strcpy(file_message.filename,filename.c_str());
    file_message.filesize=file_buffer.st_size;



    if(send_to_serv((unsigned char*)&file_message,sizeof(file_message),NET_TEST1)<0)
    {
        cout<<"向服务器发送文件信息失败"<<endl;
    }


    close(fd);
    if((fd=open(filename.c_str(),O_RDONLY))<0)
       {
           my_err("打开文件失败",__LINE__);
       }

    while(nsize=read(fd,send_buffer,sizeof(send_buffer)))
    {


        memset(&file_data,0,sizeof(file_data));
        strcpy(file_data.filename,filename.c_str());

        memcpy(file_data.buffer,send_buffer,nsize);

        send_to_serv((unsigned char*)&file_data,nsize+sizeof(file_data.filename),NET_TEST2);
        sum_size+=nsize;
    }



    if(sum_size==file_buffer.st_size)
    {
        cout<<"发送文件成功"<<endl;
        close(fd);
        return true;
    }
    else
    {
        cout<<"发送文件出错"<<endl;
        close(fd);
        return false;
    }

}

void TCPClient::run()
{
    send_file();  //向服务器发送文件
    
}

int main(int argc ,char **argv)
{
   
    TCPClient client(argc,argv);
    client.run();
    sleep(10);

}
```
