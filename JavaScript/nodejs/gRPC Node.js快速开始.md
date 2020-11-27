# gRPC Node.js快速开始

本文翻译自gRPC官网的Node.js示例，链接地址为：[https://www.grpc.io/docs/languages/node/](https://www.grpc.io/docs/languages/node/)和[Quick start](https://grpc.io/docs/languages/node/quickstart/)

![gRPC Node](https://img-blog.csdnimg.cn/20201122003333237.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)



gRPC是一个高性能、开源的通用RPC框架，其官方地址为:[https://www.grpc.io/](https://www.grpc.io/)，如下图所示：
![https://www.grpc.io/](https://img-blog.csdnimg.cn/20201122003059902.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
目前gRPC项目已经托管到Github上面，其Github仓库地址为：[https://github.com/grpc/grpc](https://github.com/grpc/grpc)
# 快速开始
本指南通过一个简单的示例使您开始在Node中使用gRPC。

## 先决条件
Node版本4.0.0或更高版本

## 下载示例
您需要本示例代码的本地副本才能完成此快速入门。 从我们的GitHub存储库下载示例代码（以下命令将克隆整个存储库，但是您仅需要有关此快速入门和其他教程的示例）：
```shell
# Clone the repository to get the example code
$ git clone -b v1.33.2 https://github.com/grpc/grpc
# Navigate to the dynamic codegen "hello, world" Node example:
$ cd grpc/examples/node/dynamic_codegen
# Install the example's dependencies
$ npm install
```

## 运行gRPC应用程序
在examples/node/dynamic_codegen目录中：
- 1.运行服务端：
```shell
$ node greeter_server.js
````

- 2.从另一个终端，运行客户端：
```shell
$ node greeter_client.js
```
恭喜你！ 您刚刚使用gRPC运行了客户端服务器应用程序。


**注意**
在gRPC服务端和客户端程序运行之前需要在本地使用`npm`或者`yarn`安装所需的依赖库。针对gRPC v1.33.2的Node版本，需要安装`grpc`和`@grpc/proto-loader`依赖库，对于目前最新的gRPC Node版本，则需要安装`@grpc/grpc-js`和`@grpc/proto-loader`依赖库。
假如使用的是gRPC  v1.33.2的Node版本的源代码，如果使用的是`npm`，在grpc/examples/node/dynamic_codegen目录下，执行如下命令：
```shell
npm init -y
npm install grpc @grpc/proto-loader
```

如果使用的是`yarn`，在grpc/examples/node/dynamic_codegen目录下，执行如下命令：
```shell
yarn init -y
yarn add grpc @grpc/proto-loader
```

下面是我在Windows10下使用[grpc github仓库](https://github.com/grpc/grpc)的最新grpc代码node示例程序运行的结果，使用之前需要安装Node.js开发环境和npm、cnpm、yarn等，然后在grpc源代码的`grpc\examples\node\dynamic_codegen`目录下使用`yarn`安装`@grpc/grpc-js`和`@grpc/proto-loader`依赖库，命令如下：
```shell
yarn init -y
yarn add @grpc/grpc-js '@grpc/proto-loader
```
然后分别运行服务端和客户端，如下图所示：
![gRPC Node服务端](https://img-blog.csdnimg.cn/20201122104833727.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
![gRPC Node客户端](https://img-blog.csdnimg.cn/2020112210503218.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)


## 更新gRPC服务
现在，让我们看一下如何使用服务器上的其他方法更新应用程序，以供客户端调用。 我们的gRPC服务是使用protocol buffers的； 您可以在[基础知识教程](https://grpc.io/docs/languages/node/basics/)中找到更多有关如何在`.proto`文件中定义服务的信息。 现在，您只需要知道服务器和客户端“stub”都有一个`SayHello `RPC方法，该方法从客户端获取`HelloRequest`参数，并从服务器返回`HelloReply`，并且该方法的定义如下：
```proto
// The greeting service definition.
service Greeter {
  // Sends a greeting
  rpc SayHello (HelloRequest) returns (HelloReply) {}
}

// The request message containing the user's name.
message HelloRequest {
  string name = 1;
}

// The response message containing the greetings
message HelloReply {
  string message = 1;
}
```

让我们对其进行更新，以使`Greeter`服务具有两种方法。 编辑`examples/protos/helloworld.proto`并使用具有相同请求和响应类型的新`SayHelloAgain`方法对其进行更新：
```proto
// The greeting service definition.
service Greeter {
  // Sends a greeting
  rpc SayHello (HelloRequest) returns (HelloReply) {}
  // Sends another greeting
  rpc SayHelloAgain (HelloRequest) returns (HelloReply) {}
}

// The request message containing the user's name.
message HelloRequest {
  string name = 1;
}

// The response message containing the greetings
message HelloReply {
  string message = 1;
}
```
记住要保存文件！

## 更新并运行应用程序
现在，我们有了一个新的服务定义，但是仍然需要在示例应用程序的人工编写部分中实现并调用新方法。

## 更新服务端
在同一目录中，打开`greeter_server.js`。 像这样实现新方法：
```js
function sayHello(call, callback) {
  callback(null, {message: 'Hello ' + call.request.name});
}

function sayHelloAgain(call, callback) {
  callback(null, {message: 'Hello again, ' + call.request.name});
}

function main() {
  var server = new grpc.Server();
  server.addService(hello_proto.Greeter.service,
                         {sayHello: sayHello, sayHelloAgain: sayHelloAgain});
  server.bind('0.0.0.0:50051', grpc.ServerCredentials.createInsecure());
  server.start();
}
```

## 更新客户端
在同一目录中，打开`greeter_client.js`。 像这样调用新方法：
```js
function main() {
  var client = new hello_proto.Greeter('localhost:50051',
                                       grpc.credentials.createInsecure());
  client.sayHello({name: 'you'}, function(err, response) {
    console.log('Greeting:', response.message);
  });
  client.sayHelloAgain({name: 'you'}, function(err, response) {
    console.log('Greeting:', response.message);
  });
}
```
## 运行！
就像我们之前一样，从examples/node/dynamic_codegen目录：

- 1.运行服务器：
```shell
$ node greeter_server.js
```

- 2.从另外一个终端，运行客户端：
```shell
$ node greeter_client.js
```
下面是我在自己购买的阿里云服务器上运行服务端和客户端的演示结果：
![运行gRPC Node服务端和客户端](https://img-blog.csdnimg.cn/20201122104237154.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70#pic_center)
## 下一步是什么
- 在[gRPC简介](https://grpc.io/docs/what-is-grpc/introduction/)和[核心概念](https://grpc.io/docs/what-is-grpc/core-concepts/)中了解gRPC的工作原理。
- 完成[基础教程](https://grpc.io/docs/languages/node/basics/)。
- 探索[API参考](https://grpc.io/docs/languages/node/api)。
- 我们为Node提供了多个grpc实现。 有关每个程序包的优缺点，请参阅此[程序包功能比较](https://github.com/grpc/grpc-node/blob/master/PACKAGE-COMPARISON.md)。

# 参考资料
- [gRPC官网](https://www.grpc.io)
- [gRPC简介](https://www.grpc.io/docs/what-is-grpc/introduction/)
- [gRPC Github仓库](https://github.com/grpc/grpc)
- [gRPC支持的语言](https://www.grpc.io/docs/languages/)
