# 用Golang构建gRPC服务

本文转载自[用Golang构建gRPC服务](https://zhuanlan.zhihu.com/p/85508384)

本教程提供了Go使用gRPC的基础教程

在教程中你将会学到如何：

- 在.proto文件中定义一个服务。
- 使用protocol buffer编译器生成客户端和服务端代码。
- 使用gRPC的Go API为你的服务写一个客户端和服务器。
继续之前，请确保你已经对[gRPC概念](https://grpc.io/docs/what-is-grpc/introduction/)有所了解，并且熟悉[protocol buffer](https://developers.google.com/protocol-buffers/docs/overview)。需要注意的是教程中的示例使用的是proto3版本的protocol buffer：你可以在[Protobuf3语言指南](https://developers.google.com/protocol-buffers/docs/proto3)与[Protobuf生成Go代码指南](https://developers.google.com/protocol-buffers/docs/reference/go-generated)中了解到更多相关知识。

## 为什么使用gRPC
我们的示例是一个简单的路线图应用，客户端可以获取路线特征信息、创建他们的路线摘要，还可以与服务器或者其他客户端交换比如交通状态更新这样的路线信息。

借助gRPC，我们可以在.proto文件中定义我们的服务，并以gRPC支持的任何语言来实现客户端和服务器，客户端和服务器又可以在从服务器到你自己的平板电脑的各种环境中运行-gRPC还会为你解决所有不同语言和环境之间通信的复杂性。我们还获得了使用protocol buffer的所有优点，包括有效的序列化（速度和体积两方面都比JSON更有效率），简单的IDL（接口定义语言）和轻松的接口更新。

## 安装
### 安装grpc包
首先需要安装gRPC golang版本的软件包，同时官方软件包的examples目录里就包含了教程中示例路线图应用的代码。
```shell
$ go get google.golang.org/grpc
```
然后切换到`grpc-go/examples/route_guide:`目录：
```shell
$ cd $GOPATH/src/google.golang.org/grpc/examples/route_guide
```

### 安装相关工具和插件
- 安装protocol buffer编译器
安装编译器最简单的方式是去[https://github.com/protocolbuffers/protobuf/releases](https://github.com/protocolbuffers/protobuf/releases) 下载预编译好的protoc二进制文件，仓库中可以找到每个平台对应的编译器二进制文件。这里我们以Mac Os为例，从[https://github.com/protocolbuffers/protobuf/releases/download/v3.6.0/protoc-3.6.0-osx-x86_64.zip](https://github.com/protocolbuffers/protobuf/releases/download/v3.6.0/protoc-3.6.0-osx-x86_64.zip) 下载并解压文件。
更新`PATH`系统变量，或者确保`protoc`放在了`PATH`包含的目录中了。
- 安装protoc编译器插件
```shell
$ go get -u github.com/golang/protobuf/protoc-gen-go
```
编译器插件`protoc-gen-go`将安装在`$GOBIN`中，默认位于`​$GOPATH/bin`。编译器`protoc`必须在`$PATH`中能找到它：
```shell
$ export PATH=$PATH:$GOPATH/bin
```

## 定义服务
首先第一步是使用protocol buffer定义gRPC服务还有方法的请求和响应类型，你可以在下载的示例代码[examples/route_guide/routeguide/route_guide.proto](https://link.zhihu.com/?target=https%3A//github.com/grpc/grpc-go/blob/master/examples/route_guide/routeguide/route_guide.proto)中看到完整的.proto文件。

要定义服务，你需要在`.proto`文件中指定一个具名的`service`
```proto
service RouteGuide {
   ...
}
```

然后在服务定义中再来定义`rpc`方法，指定他们的请求和响应类型。gRPC允许定义四种类型的服务方法，这四种服务方法都会应用到我们的`RouteGuide`服务中。

- 一个简单的RPC，客户端使用存根将请求发送到服务器，然后等待响应返回，就像普通的函数调用一样。
```go
// 获得给定位置的特征
rpc GetFeature(Point) returns (Feature) {}
```

- 服务器端流式RPC，客户端向服务器发送请求，并获取流以读取回一系列消息。客户端从返回的流中读取，直到没有更多消息为止。如我们的示例所示，可以通过将stream关键字放在响应类型之前来指定服务器端流方法。
```go
//获得给定Rectangle中可用的特征。结果是
//流式传输而不是立即返回
//因为矩形可能会覆盖较大的区域并包含大量特征。
rpc ListFeatures(Rectangle) returns (stream Feature) {}
```

- 客户端流式RPC，其中客户端使用gRPC提供的流写入一系列消息并将其发送到服务器。客户端写完消息后，它将等待服务器读取所有消息并返回其响应。通过将stream关键字放在请求类型之前，可以指定客户端流方法。
```go
// 接收路线上被穿过的一系列点位, 当行程结束时
// 服务端会返回一个RouteSummary类型的消息.
rpc RecordRoute(stream Point) returns (RouteSummary) {}
```

- 双向流式RPC，双方都使用读写流发送一系列消息。这两个流是独立运行的，因此客户端和服务器可以按照自己喜欢的顺序进行读写：例如，服务器可以在写响应之前等待接收所有客户端消息，或者可以先读取消息再写入消息，或其他一些读写组合。每个流中的消息顺序都会保留。您可以通过在请求和响应之前都放置stream关键字来指定这种类型的方法。
```go
//接收路线行进中发送过来的一系列RouteNotes类型的消息，同时也接收其他RouteNotes(例如：来自其他用户)
rpc RouteChat(stream RouteNote) returns (stream RouteNote) {}
```

我们的`.proto`文件中也需要所有请求和响应类型的protocol buffer消息类型定义。比如说下面的Point消息类型：
```proto
// Points被表示为E7表示形式中的经度-纬度对。
//（度数乘以10 ** 7并四舍五入为最接近的整数）。
// 纬度应在+/- 90度范围内，而经度应在
// 范围+/- 180度（含）
message Point {
  int32 latitude = 1;
  int32 longitude = 2;
}
```

## 生成客户端和服务端代码
接下来要从我们的`.proto`服务定义生成gRPC客户端和服务端的接口。我们使用`protoc`编译器和上面安装的编译器插件来完成这些工作：

在示例`route_guide`的目录下运行：
```shell
protoc -I routeguide/ routeguide/route_guide.proto --go_out=plugins=grpc:routeguide
```
运行命令后会在示例`route_guide`目录的`routeguide`目录下生成`route_guide.pb.go`文件。

`pb.go`文件里面包含：
- 用于填充、序列化和检索我们定义的请求和响应消息类型的所有protocol buffer代码。
- 一个客户端存根用来让客户端调用`RouteGuide`服务中定义的方法。
- 一个需要服务端实现的接口类型`RouteGuideServer`，接口类型中包含了`RouteGuide`服务中定义的所有方法。

## 创建gRPC服务端
首先让我们看一下怎么创建`RouteGuide`服务器。有两种方法来让我们的`RouteGuide`服务工作：

- 实现我们从服务定义生成的服务接口：做服务实际要做的事情。
- 运行一个gRPC服务器监听客户端的请求然后把请求派发给正确的服务实现。
你可以在刚才安装的gPRC包的grpc-[go/examples/route_guide/server/server.go](https://link.zhihu.com/?target=https%3A//github.com/grpc/grpc-go/tree/master/examples/route_guide/server/server.go)找到我们示例中RouteGuide`服务的实现代码。下面让我们看看他是怎么工作的。

## 实现RouteGuide
如你所见，实现代码中有一个`routeGuideServer`结构体类型，它实现了`protoc`编译器生成的`pb.go`文件中定义的`RouteGuideServer`接口。
```go
type routeGuideServer struct {
        ...
}
...

func (s *routeGuideServer) GetFeature(ctx context.Context, point *pb.Point) (*pb.Feature, error) {
        ...
}
...

func (s *routeGuideServer) ListFeatures(rect *pb.Rectangle, stream pb.RouteGuide_ListFeaturesServer) error {
        ...
}
...

func (s *routeGuideServer) RecordRoute(stream pb.RouteGuide_RecordRouteServer) error {
        ...
}
...

func (s *routeGuideServer) RouteChat(stream pb.RouteGuide_RouteChatServer) error {
        ...
}
...
```

## 普通PRC
`routeGuideServer`实现我们所有的服务方法。首先，让我们看一下最简单的类型GetFeature，它只是从客户端获取一个`Point`，并从其`Feature`数据库中返回相应的`Feature`信息。
```go
func (s *routeGuideServer) GetFeature(ctx context.Context, point *pb.Point) (*pb.Feature, error) {
    for _, feature := range s.savedFeatures {
        if proto.Equal(feature.Location, point) {
            return feature, nil
        }
    }
    // No feature was found, return an unnamed feature
    return &pb.Feature{"", point}, nil
}
```
这个方法传递了RPC上下文对象和客户端的`Point` protocol buffer请求消息，它在响应信息中返回一个`Feature`类型的protocol buffer消息和错误。在该方法中，我们使用适当的信息填充`Feature`，然后将其返回并返回nil错误，以告知gRPC我们已经完成了RPC的处理，并且可以将`Feature`返回给客户端。

## 服务端流式RPC
现在，让我们看一下服务方法中的一个流式RPC。 `ListFeatures`是服务器端流式RPC，因此我们需要将多个`Feature`发送回客户端。
```go
func (s *routeGuideServer) ListFeatures(rect *pb.Rectangle, stream pb.RouteGuide_ListFeaturesServer) error {
    for _, feature := range s.savedFeatures {
        if inRange(feature.Location, rect) {
            if err := stream.Send(feature); err != nil {
                return err
            }
        }
    }
    return nil
}
```

如你所见，这次我们没有获得简单的请求和响应对象，而是获得了一个请求对象（客户端要在其中查找`Feature`的`Rectangle`）和一个特殊的`RouteGuide_ListFeaturesServer`对象来写入响应。

在该方法中，我们填充了需要返回的所有`Feature`对象，并使用`Send()方`法将它们写入`RouteGuide_ListFeaturesServer`。最后，就像在简单的RPC中一样，我们返回`nil`错误来告诉gRPC我们已经完成了响应的写入。如果此调用中发生任何错误，我们将返回非`nil`错误； gRPC层会将其转换为适当的RPC状态，以在线上发送。

## 客户端流式RPC
现在，让我们看一些更复杂的事情：客户端流方法`RecordRoute`，从客户端获取点流，并返回一个包含行程信息的`RouteSummary`。如你所见，这一次该方法根本没有request参数。相反，它获得一个`RouteGuide_RecordRouteServer`流，服务器可以使用该流来读取和写入消息-它可以使用`Recv()`方法接收客户端消息，并使用`SendAndClose()`方法返回其单个响应。
```go
func (s *routeGuideServer) RecordRoute(stream pb.RouteGuide_RecordRouteServer) error {
    var pointCount, featureCount, distance int32
    var lastPoint *pb.Point
    startTime := time.Now()
    for {
        point, err := stream.Recv()
        if err == io.EOF {
            endTime := time.Now()
            return stream.SendAndClose(&pb.RouteSummary{
                PointCount:   pointCount,
                FeatureCount: featureCount,
                Distance:     distance,
                ElapsedTime:  int32(endTime.Sub(startTime).Seconds()),
            })
        }
        if err != nil {
            return err
        }
        pointCount++
        for _, feature := range s.savedFeatures {
            if proto.Equal(feature.Location, point) {
                featureCount++
            }
        }
        if lastPoint != nil {
            distance += calcDistance(lastPoint, point)
        }
        lastPoint = point
    }
}
```

在方法主体中，我们使用`RouteGuide_RecordRouteServer`的`Recv()`方法不停地读取客户端的请求到一个请求对象中（在本例中为`Point`），直到没有更多消息为止：服务器需要要在每次调用后检查从`Recv()`返回的错误。如果为`nil`，则流仍然良好，并且可以继续读取；如果是io.EOF，则表示消息流已结束，服务器可以返回其RouteSummary。如果错误为其他值，我们将返回错误“原样”，以便gRPC层将其转换为RPC状态。

## 双向流式RPC
最后让我们看一下双向流式RPC方法RouteChat()
```go
func (s *routeGuideServer) RouteChat(stream pb.RouteGuide_RouteChatServer) error {
    for {
        in, err := stream.Recv()
        if err == io.EOF {
            return nil
        }
        if err != nil {
            return err
        }
        key := serialize(in.Location)

        s.mu.Lock()
        s.routeNotes[key] = append(s.routeNotes[key], in)
        // Note: this copy prevents blocking other clients while serving this one.
        // We don't need to do a deep copy, because elements in the slice are
        // insert-only and never modified.
        rn := make([]*pb.RouteNote, len(s.routeNotes[key]))
        copy(rn, s.routeNotes[key])
        s.mu.Unlock()

        for _, note := range rn {
            if err := stream.Send(note); err != nil {
                return err
            }
        }
    }
}
```

这次，我们得到一个`RouteGuide_RouteChatServer`流，就像在客户端流示例中一样，该流可用于读取和写入消息。但是，这次，当客户端仍在向其消息流中写入消息时，我们会向流中写入要返回的消息。

此处的读写语法与我们的客户端流式传输方法非常相似，不同之处在于服务器使用流的`Send()`方法而不是`SendAndClose()`，因为服务器会写入多个响应。尽管双方总是会按照对方的写入顺序来获取对方的消息，但是客户端和服务器都可以以任意顺序进行读取和写入-流完全独立地运行（意思是服务器可以接受完请求后再写流，也可以接收一条请求写一条响应。同样的客户端可以写完请求了再读响应，也可以发一条请求读一条响应）

## 启动服务器
一旦实现了所有方法，我们还需要启动gRPC服务器，以便客户端可以实际使用我们的服务。以下代码段显示了如何启动`RouteGuide`服务。
```go
flag.Parse()
lis, err := net.Listen("tcp", fmt.Sprintf(":%d", *port))
if err != nil {
        log.Fatalf("failed to listen: %v", err)
}
grpcServer := grpc.NewServer()
pb.RegisterRouteGuideServer(grpcServer, &routeGuideServer{})
... // determine whether to use TLS
grpcServer.Serve(lis)
```

为了构建和启动服务器我们需要：

- 指定要监听客户端请求的接口`lis, err := net.Listen("tcp", fmt.Sprintf(":%d", *port))`。
- 使用`grpc.NewServer()`创建一个gRPC server的实例。
- 使用gRPC server注册我们的服务实现。
- 使用我们的端口详细信息在服务器上调用`Serve()`进行阻塞等待，直到进程被杀死或调用`Stop()`为止。

## 创建客户端
在这一部分中我们将为RouteGuide服务创建Go客户端，你可以在[grpc-go/examples/route_guide/client/client.go](https://link.zhihu.com/?target=https%3A//github.com/grpc/grpc-go/tree/master/examples/route_guide/client/client.go) 看到完整的客户端代码。

## 创建客户端存根
要调用服务的方法，我们首先需要创建一个gRPC通道与服务器通信。我们通过把服务器地址和端口号传递给`grpc.Dial()`来创建通道，像下面这样：
```go
conn, err := grpc.Dial(*serverAddr)
if err != nil {
    ...
}
defer conn.Close()
```

如果你请求的服务需要认证，你可以在`grpc.Dial`中使用`DialOptions`设置认证凭证（比如：TLS，GCE凭证，JWT凭证）--不过我们的`RouteGuide`服务不需要这些。

设置gRPC通道后，我们需要一个客户端存根来执行RPC。我们使用从`.proto`生成的`pb`包中提供的`NewRouteGuideClient`方法获取客户端存根。
```go
client := pb.NewRouteGuideClient(conn)
```

生成的`pb.go`文件定义了客户端接口类型`RouteGuideClient`并用客户端存根的结构体类型实现了接口中的方法，所以通过上面获取到的客户端存根`client`可以直接调用下面接口类型中列出的方法。
```go
type RouteGuideClient interface {
    GetFeature(ctx context.Context, in *Point, opts ...grpc.CallOption) (*Feature, error)

    ListFeatures(ctx context.Context, in *Rectangle, opts ...grpc.CallOption) (RouteGuide_ListFeaturesClient, error)

    RecordRoute(ctx context.Context, opts ...grpc.CallOption) (RouteGuide_RecordRouteClient, error)
    RouteChat(ctx context.Context, opts ...grpc.CallOption) (RouteGuide_RouteChatClient, error)
}
```

每个实现方法会再去请求gRPC服务端相对应的方法获取服务端的响应，比如：
```go
func (c *routeGuideClient) GetFeature(ctx context.Context, in *Point, opts ...grpc.CallOption) (*Feature, error) {
    out := new(Feature)
    err := c.cc.Invoke(ctx, "/routeguide.RouteGuide/GetFeature", in, out, opts...)
    if err != nil {
        return nil, err
    }
    return out, nil
}
```

`RouteGuideClient`接口的完整实现可以在生成的`pb.go`文件里找到。

## 调用服务的方法
现在让我们看看如何调用服务的方法。注意在gRPC-Go中，PRC是在阻塞/同步模式下的运行的，也就是说RPC调用会等待服务端响应，服务端将返回响应或者是错误。

## 普通RPC
调用普通RPC方法GetFeature如同直接调用本地的方法。
```go
feature, err := client.GetFeature(context.Background(), &pb.Point{409146138, -746188906})
if err != nil {
        ...
}
```
如你所见，我们在之前获得的存根上调用该方法。在我们的方法参数中，我们创建并填充一个protocol buffer对象（在本例中为Point对象）。我们还会传递一个`context.Context`对象，该对象可让我们在必要时更改RPC的行为，例如超时/取消正在调用的RPC（cancel an RPC in flight）。如果调用没有返回错误，则我们可以从第一个返回值中读取服务器的响应信息。

## 服务端流式RPC
这里我们会调用服务端流式方法`ListFeatures`，方法返回的流中包含了地理特征信息。如果你读过上面的创建客户端的章节，这里有些东西看起来会很熟悉--流式RPC在两端实现的方式很类似。
```go
rect := &pb.Rectangle{ ... }  // initialize a pb.Rectangle
stream, err := client.ListFeatures(context.Background(), rect)
if err != nil {
    ...
}
for {
    feature, err := stream.Recv()
    if err == io.EOF {
        break
    }
    if err != nil {
        log.Fatalf("%v.ListFeatures(_) = _, %v", client, err)
    }
    log.Println(feature)
}
```

和简单RPC调用一样，调用时传递了一个方法的上下文和一个请求。但是我们取回的是一个`RouteGuide_ListFeaturesClient`实例而不是一个响应对象。客户端可以使用`RouteGuide_ListFeaturesClient`流读取服务器的响应。

我们使用`RouteGuide_ListFeaturesClient`的`Recv()`方法不停地将服务器的响应读入到一个protocol buffer响应对象中（本例中的`Feature`对象），直到没有更多消息为止：客户端需要在每次调用后检查从`Recv()`返回的错误`err`。如果为`nil`，则流仍然良好，并且可以继续读取；如果是`io.EOF`，则消息流已结束；否则就是一定RPC错误，该错误会通过`err`传递给调用程序。

## 客户端流式RPC
客户端流方法`RecordRoute`与服务器端方法相似，不同之处在于，我们仅向该方法传递一个上下文并获得一个`RouteGuide_RecordRouteClient`流，该流可用于写入和读取消息。
```go
// 随机的创建一些Points
r := rand.New(rand.NewSource(time.Now().UnixNano()))
pointCount := int(r.Int31n(100)) + 2 // Traverse at least two points
var points []*pb.Point
for i := 0; i < pointCount; i++ {
    points = append(points, randomPoint(r))
}
log.Printf("Traversing %d points.", len(points))
stream, err := client.RecordRoute(context.Background())// 调用服务中定义的客户端流式RPC方法
if err != nil {
    log.Fatalf("%v.RecordRoute(_) = _, %v", client, err)
}
for _, point := range points {
    if err := stream.Send(point); err != nil {// 向流中写入多个请求消息
        if err == io.EOF {
            break
        }
        log.Fatalf("%v.Send(%v) = %v", stream, point, err)
    }
}
reply, err := stream.CloseAndRecv()// 从流中取回服务器的响应
if err != nil {
    log.Fatalf("%v.CloseAndRecv() got error %v, want %v", stream, err, nil)
}
log.Printf("Route summary: %v", reply)
```

`RouteGuide_RecordRouteClient`有一个`Send()`。我们可以使用它发送请求给服务端。一旦我们使用`Send()`写入流完成后，我们需要在流上调用`CloseAndRecv()`方法让gRPC知道我们已经完成了请求的写入并且期望得到一个响应。我们从`CloseAndRecv()`方法返回的err中可以获得RPC状态。如果状态是`nil`,`CloseAndRecv()`的第一个返回值就是一个有效的服务器响应。

## 双向流式RPC
最后，让我们看一下双向流式RPC `RouteChat()`。与`RecordRoute`一样，我们只向方法传递一个上下文对象，然后获取一个可用于写入和读取消息的流。但是，这一次我们在服务器仍将消息写入消息流的同时，通过方法的流返回值。
```go
stream, err := client.RouteChat(context.Background())
waitc := make(chan struct{})
go func() {
    for {
        in, err := stream.Recv()
        if err == io.EOF {
            // read done.
            close(waitc)
            return
        }
        if err != nil {
            log.Fatalf("Failed to receive a note : %v", err)
        }
        log.Printf("Got message %s at point(%d, %d)", in.Message, in.Location.Latitude, in.Location.Longitude)
    }
}()
for _, note := range notes {
    if err := stream.Send(note); err != nil {
        log.Fatalf("Failed to send a note: %v", err)
    }
}
stream.CloseSend()
<-waitc
```
除了在完成调用后使用流的`CloseSend()`方法外，此处的读写语法与我们的客户端流方法非常相似。尽管双方总是会按照对方的写入顺序来获取对方的消息，但是客户端和服务器都可以以任意顺序进行读取和写入-两端的流完全独立地运行。

## 启动应用
要编译和运行服务器，假设你位于`$GOPATH/src/google.golang.org/grpc/examples/route_guide`文件夹中，只需：
```shell
$ go run server/server.go
```

同样，运行客户端：
```shell
$ go run client/client.go
```
你将看到如下输出：
```shell
Getting feature for point (409146138, -746188906)
name:"Berkshire Valley Management Area Trail, Jefferson, NJ, USA" location:<latitude:409146138 longitude:-746188906 >
Getting feature for point (0, 0)
location:<>
Looking for features within lo:<latitude:400000000 longitude:-750000000 > hi:<latitude:420000000 longitude:-730000000 >
name:"Patriots Path, Mendham, NJ 07945, USA" location:<latitude:407838351 longitude:-746143763 >
...
name:"3 Hasta Way, Newton, NJ 07860, USA" location:<latitude:410248224 longitude:-747127767 >
Traversing 56 points.
Route summary: point_count:56 distance:497013163
Got message First message at point(0, 1)
Got message Second message at point(0, 2)
Got message Third message at point(0, 3)
Got message First message at point(0, 1)
Got message Fourth message at point(0, 1)
Got message Second message at point(0, 2)
Got message Fifth message at point(0, 2)
Got message Third message at point(0, 3)
Got message Sixth message at point(0, 3)
```

## 参考资料
- [用Golang构建gRPC服务](https://zhuanlan.zhihu.com/p/85508384)
- [gRPC Basics tutorial- Go](https://grpc.io/docs/languages/go/basics/)
- [gRPC Quick start-Go](https://grpc.io/docs/languages/go/basics/)
- [https://github.com/grpc/grpc-go](https://github.com/grpc/grpc-go)
- [gRPC Hello World](https://github.com/grpc/grpc-go/tree/master/examples)
- 
