本文转载自[Go语言实现TCP通信](http://topgoer.com/%E7%BD%91%E7%BB%9C%E7%BC%96%E7%A8%8B/socket%E7%BC%96%E7%A8%8B/TCP%E7%BC%96%E7%A8%8B.html)

## Go语言实现TCP通信
### TCP协议
TCP/IP(Transmission Control Protocol/Internet Protocol) 即传输控制协议/网间协议，是一种面向连接（连接导向）的、可靠的、基于字节流的传输层（Transport layer）通信协议，因为是面向连接的协议，数据像水流一样传输，会存在黏包问题。

### TCP服务端
一个TCP服务端可以同时连接很多个客户端，例如世界各地的用户使用自己电脑上的浏览器访问淘宝网。因为Go语言中创建多个goroutine实现并发非常方便和高效，所以我们可以每建立一次链接就创建一个goroutine去处理。

TCP服务端程序的处理流程：
- 1..监听端口
-  2.接收客户端请求建立连接
-  3.创建goroutine处理连接。

我们使用Go语言的net包实现的TCP服务端代码`server/server.go`如下：
```go
package main

import (
	"bufio"
	"fmt"
	"net"
)

// TCP Server端测试
// 处理函数
func process(conn net.Conn) {
	defer conn.Close() // 关闭连接
	for {
		reader := bufio.NewReader(conn)
		var buf [128]byte
		n, err := reader.Read(buf[:]) // 读取数据
		if err != nil {
			fmt.Println("read from client failed, err: ", err)
			break
		}
		recvStr := string(buf[:n])
		fmt.Println("收到Client端发来的数据：", recvStr)
		conn.Write([]byte(recvStr)) // 发送数据
	}
}

func main() {
	listen, err := net.Listen("tcp", "127.0.0.1:9999")
	if err != nil {
		fmt.Println("Listen() failed, err: ", err)
		return
	}
	for {
		conn, err := listen.Accept() // 监听客户端的连接请求
		if err != nil {
			fmt.Println("Accept() failed, err: ", err)
			continue
		}
		go process(conn) // 启动一个goroutine来处理客户端的连接请求
	}
}

```
将上面的代码保存之后编译成server或server.exe可执行文件。


### TCP客户端
一个TCP客户端进行TCP通信的流程如下：
-  1.建立与服务端的连接
- 2.进行数据收发
- 3.关闭连接

使用Go语言的net包实现的TCP客户端代码`client/client.go`如下：
```go
package main

import (
	"bufio"
	"fmt"
	"net"
	"os"
	"strings"
)

// TCP 客户端
func main() {
	conn, err := net.Dial("tcp", "127.0.0.1:9999")
	if err != nil {
		fmt.Println("err : ", err)
		return
	}
	defer conn.Close() // 关闭TCP连接
	inputReader := bufio.NewReader(os.Stdin)
	for {
		input, _ := inputReader.ReadString('\n') // 读取用户输入
		inputInfo := strings.Trim(input, "\r\n")
		if strings.ToUpper(inputInfo) == "Q" { // 如果输入q就退出
			return
		}
		_, err := conn.Write([]byte(inputInfo)) // 发送数据
		if err != nil {
			return
		}
		buf := [512]byte{}
		n, err := conn.Read(buf[:])
		if err != nil {
			fmt.Println("recv failed, err:", err)
			return
		}
		fmt.Println(string(buf[:n]))
	}
}

```
将上面的代码编译成client或client.exe可执行文件，先启动server端再启动client端，在client端输入任意内容回车之后就能够在server端看到client端发送的数据，从而实现TCP通信。

下面是我在CentOS7下运行的测试：
![Go实现的TCP服务端和客户端测试](https://img-blog.csdnimg.cn/20201021125325143.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
