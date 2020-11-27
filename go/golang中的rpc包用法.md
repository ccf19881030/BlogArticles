# golang中的rpc包用法

RPC，即 Remote Procedure Call（远程过程调用），说得通俗一点就是：调用远程计算机上的服务，就像调用本地服务一样。

我所在公司的项目是采用基于Restful的微服务架构，随着微服务之间的沟通越来越频繁，就希望可以做成用rpc来做内部的通讯，对外依然用Restful。于是就想到了golang标准库的rpc包和google的grpc。

这篇文章重点了解一下golang的rpc包。

## 介绍
golang的rpc支持三个级别的RPC：TCP、HTTP、JSONRPC。但Go的RPC包是独一无二的RPC，它和传统的RPC系统不同，它只支持Go开发的服务器与客户端之间的交互，因为在内部，它们采用了Gob来编码。

Go RPC的函数只有符合下面的条件才能被远程访问，不然会被忽略，详细的要求如下：
- 函数必须是导出的(首字母大写)
- 必须有两个导出类型的参数，
- 第一个参数是接收的参数，第二个参数是返回给客- 户端的参数，第二个参数必须是指针类型的
- 函数还要有一个返回值error

举个例子，正确的RPC函数格式如下：
```go
func (t *T) MethodName(argType T1, replyType *T2) error
```
T、T1和T2类型必须能被`encoding/gob`包编解码。

## 示例
举一个http的例子。

下面是http服务器端的代码：
```go
package main

import (
	"errors"
	"net"
	"net/rpc"
	"log"
	"net/http"
)

type Args struct {
	A, B int
}

type Quotient struct {
	Quo, Rem int
}

type Arith int

func (t *Arith) Multiply(args *Args, reply *int) error {
	*reply = args.A * args.B
	return nil
}

func (t *Arith) Divide(args *Args, quo *Quotient) error {
	if args.B == 0 {
		return errors.New("divide by zero")
	}
	quo.Quo = args.A / args.B
	quo.Rem = args.A % args.B
	return nil
}

func main() {
	arith := new(Arith)
	rpc.Register(arith)
	rpc.HandleHTTP()
	l, e := net.Listen("tcp", ":1234")
	if e != nil {
		log.Fatal("listen error:", e)
	}
	http.Serve(l, nil)
}
```

简单分析一下上面的例子，先实例化了一个Arith对象arith，然后给arith注册了rpc服务，然后把rpc挂载到http服务上面，当http服务打开的时候我们就可以通过rpc客户端来调用arith中符合rpc标准的的方法了。

请看客户端的代码：
```go
package main

import (
	"net/rpc"
	"log"
	"fmt"
)

type Args struct {
	A, B int
}

type Quotient struct {
	Quo, Rem int
}

func main()  {
	client, err := rpc.DialHTTP("tcp", "127.0.0.1:1234")
	if err != nil {
		log.Fatal("dialing:", err)
	}

	// Synchronous call
	args := &Args{7,8}
	var reply int
	err = client.Call("Arith.Multiply", args, &reply)
	if err != nil {
		log.Fatal("arith error:", err)
	}
	fmt.Printf("Arith: %d*%d=%d\n", args.A, args.B, reply)

	// Asynchronous call
	quotient := new(Quotient)
	divCall := client.Go("Arith.Divide", args, quotient, nil)
	replyCall := <-divCall.Done	// will be equal to divCall
	if replyCall.Error != nil {
		log.Fatal("arith error:", replyCall.Error)
	}
	fmt.Printf("Arith: %d/%d=%d...%d", args.A, args.B, quotient.Quo, quotient.Rem)
	// check errors, print, etc.
}
```

简单说明下，先用rpc的DialHTTP方法连接服务器端，调用服务器端的函数就要使用Call方法了，Call方法的参数和返回值已经很清晰的表述出rpc整体的调用逻辑了。

我们把服务器端跑起来，再把客户端跑起来，这时候客户端会输出：
```shell
Arith: 7*8=56
Arith: 7/8=0...7
```
下面是我在阿里云CentOS8服务器下的测试结果截图，如下图所示：
![rpc测试](https://img-blog.csdnimg.cn/20201123154513109.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)

到此，整个rpc的调用逻辑就完成了。

## 参考资料
- [golang中的rpc包用法](https://www.cnblogs.com/andyidea/p/6525714.html)
- [rpc - The Go Programming Language](https://documentation.help/Golang/net_rpc.htm)
- [https://pkg.go.dev/net/rpc](https://pkg.go.dev/net/rpc)
- [Go RPC 开发指南](https://pkg.go.dev/net/rpc)
- [Go 语言实现 RPC 调用](https://zhuanlan.zhihu.com/p/183231254)
