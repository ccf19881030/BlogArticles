## [在 Ajax 应用程序中实现实时数据推送](https://www.ibm.com/developerworks/cn/web/wa-aj-socket/)
### 简介
Ajax 技术已经存在了一段时间，开发的动力已经真正开始得到了人们的认可。越来越多的 Web 站点正在考虑使用 Ajax 进行设计，开发人员也开始将 Ajax 的能力发挥到极限。随着社交网络和协作式报告等现象的出现，一组全新的要求浮现出来。如果有其他用户更改了某位用户正在观察的任何活动，则用户希望得到通知。如果一个 Web 站点显示动态数据，如股价等，那么所有用户都必须立即得到关于变更的通知。

这些场景本身属于一类称为 “服务器推送” 的问题。通常，服务器是中心实体，服务器将首先获得关于所发生的任何更改的通知，服务器负责将此类更改通知所有连接的客户端。但遗憾的是，HTTP 是客户端-服务器通信的标准协议，它是无状态的，而且在某种意义上来说，也是一种单向的协议。HTTP 场景中的所有通信都必须由客户端发起，至服务器结束，然而我们所提到的场景的需求则完全相反。对于服务器推送来说，需要由服务器发起通信，并向客户端发送数据。HTTP 协议并无相关配置，Web 站点应用程序开发人员使用独创的方法来绕过这些问题，例如轮询，客户端会以固定（或可配置）的时间间隔与服务器联系，查找是否有新更新可用。在大多数时候，这些轮询纯粹是浪费，因而服务器没有任何更新。这种方法不是没有代价的，它有两大主要问题。

这种方法极度浪费网络资源。每一个轮询请求通常都会创建一个 TCP 套接字连接（除非 HTTP 1.1 将自己的 keepAlive 设置为 true，此时将使用之前创建的套接字）。套接字连接本身代价极高。除此之外，每一次请求都要在网络上传输一些数据，如果请求未在服务器上发现任何更新，那么这样的数据传输就是浪费资源。如果在客户端机器上还运行着其他应用程序，那么这些轮询会减少传输数据可用的带宽。
即便是请求成功，确实为客户端传回了更新，考虑到轮询的频率，这样的更新也不是实时的。例如，假设轮询配置为每 20 秒一次，就在一次请求刚刚从服务器返回时，发生了更新。那么这次更新将在 20 秒后的下一次请求到来时才能返回客户端。因而，服务器上准备好供客户端使用的更新必须等待一段时间，才能真正地为客户端所用。对于需要以尽可能实时的方式运行的应用程序来说，这样的等待是不可接受的。
考虑到这样两个问题，对于需要关键、实时的服务器端更新的企业应用程序而言，轮询并不是最理想的方法。在这篇文章中，我将介绍多种可以替代轮询的方法。每一种替代方法在某些场景中都有自己的突出之处。我将说明这些场景，并展示需要实时服务器推送的一组 UI。

Ajax 应用程序中的服务器更新技术
让我们来具体看看用于更新来自服务器的信息的一些常用技术，这些技术模拟了服务器推送。

短轮询
短轮询也称为高频轮询，就是我在本文开头处介绍的技术。这种方法在以下情况中表现最好：

有足够的带宽可用。
根据统计数据，大多数时候，请求都能获得更新。例如，股市数据就总是有可用更新。
使用 HTTP 1.1 协议。设置 keepAlive=true，因而，同一个套接字连接始终保持活动状态，并可重用。

长轮询
长轮询是用于更新服务器数据的另外一种方法。这种方法的理念就是客户端建立连接，服务器阻塞连接（通过使请求线程在某些条件下处于等待状态），有数据可用时，服务器将通过阻塞的连接发送数据，随后关闭连接。客户端在接收到更新后，立即重新建立连接，服务器重复上述过程，以此实现近于实时的通信。然而，长轮询具有以下缺陷：

一般的浏览器默认允许每台服务器具有两个连接。在这种情况下，一个连接始终是繁忙状态。因而，UI 只有一个连接（也就是说，能力减半）可用于为用户请求提供服务。这可能会导致某些操作的性能降低。
仍然需要打开和关闭 HTTP 连接，如果采用的是非持久连接模式（keepAlive=false），那么这种方法的代价可能极高。
这种方法近于实时，但并非真正的实时。（当然，某些外部因素总是不可控的，比如网络延时，在任何方法中都会存在这些因素。）
流通道
流通道（streaming channel）与长轮询大致相同，差别在于服务器不会关闭响应流。而是特意保持其处于打开状态，使浏览器认为还有更多数据即将到来。但是，流通道也有着自己的缺陷：

最大的问题就是数据刷新（flushing）。过去，Web 服务器会缓存响应数据，仅在接受到足够的字节数或块数后才会发送出去。在这种情况下，即便应用程序刷新数据，也仍然会由服务器缓存，以实现优化。更糟的是，如果在客户端和服务器之间存在代理服务器，那么代理也可能会为自身之便缓存数据。
如果发现套接字将打开较长的时间，某些浏览器实现可能会自行决定关闭套接字。在这种情况下，通道需要重新建立。
通常，第一个问题可通过为每个流响应附加垃圾有效载荷来解决，使响应数据足以填满缓冲区。第二个问题可通过 “保持活动” 或按固定间隔 “同步” 消息来欺瞒浏览器，使浏览器认为数据是以较慢的速率传入的。

这些解决方案适用的用例范围狭窄。所有这些方法都已经在 Internet 上的某些解决方案中得到了应用。然而，这些解决方案都遭遇了相同的问题：缺乏可伸缩性。典型情况下，要阻塞一个请求，您需要阻塞处理请求的线程，因为如今几乎所有应用服务器都会执行阻塞 I/O。即便不是这样，Java™ 2 Platform, Enterprise Edition (J2EE) 也未提供为 HTTP 请求和响应执行非阻塞 I/O 的标准。（Servlets 3.0 API 可解决这一问题，因为这些 API 中包含 Comet Servlet。）

至此，您需要具备非阻塞 I/O（NIO）服务器，客户端应用程序通过它进行连接。由于此类套接字是纯 TCP 二进制套接字，因而将实现以下目标：

由于服务器端具有 NIO，因而可实现更高的可伸缩性。
响应缓存的问题不复存在，因为这个套接字直接受应用程序的控制。
基于上述说明，有必要指出这种方法的四个缺点：

由于使用的是二进制 TCP 套接字，因而应用程序无法真正地利用 HTTPS 层提供的 SSL 安全性。所以，要求数据安全性的应用程序可能需要提供自己的加密工具。
通常情况下，服务器套接字将在 80 以外的端口上运行，如果防火墙仅允许来自端口 80 的流量，将出现问题。因而，可能需要进行一些端口配置。
Ajax 客户端无法通过后端打开 TCP 套接字连接。
即便 Ajax 客户端能够执行 open 函数，也无法理解二进制内容，这是因为 Ajax 使用的是 XML 或 JSON（基于文本）格式。
在这篇文章中，我要强调的是如何真正地绕开第三个和第四个问题。如果您能够处理安全性和防火墙问题，那么其他问题也能得到处理。这种做法的获益极为显著。

您可为应用程序实现最大程度的实时服务器推送行为（不考虑网络延时等外部因素），您将获得高度可伸缩的解决方案（以同时连接的客户端数量为准）。

下面我们将开始探索如何解决上述的第三个和第四个问题。

基于套接字的 RIA 技术
Ajax 并不能真正地解决第三个和第四个问题。因而，您需要利用其他 RIA 技术寻求解决方案。有两种 RIA 技术提供的套接字 API 可与 Ajax 应用程序交互。这两种技术是 Adobe Flex 和 OpenLaszlo。全面介绍这两种技术并非本文讨论范围之内（更多信息请参见 参考资料），但这些技术提供的两种特性如下所示：

均能通过后端打开 TCP 二进制套接字
均能出色地与运行在同一个浏览器窗口中的 Ajax 应用程序（主要是 JavaScript）交互
但这仅仅解决了部分问题。您确实可以打开套接字，可以使 Ajax 应用程序使用它们，但 Ajax 应用程序仍然无法处理纯二进制数据。这又该怎么办？实际上，这两种技术都提供了二进制 TCP 套接字的一种变体，称为 XMLSocket，它可用于来回传输纯 XML 数据。这正是您需要的东西。如果这些技术能够通过服务器打开套接字，如果它们能够传输 XML 数据，我们的任务就完成了。Ajax 应用程序可充分利用这一点，模拟实时服务器推送技术。下面将介绍如何实现。

实现 Ajax 服务器推送
我将使用两种工具解释这项技术：Adobe Flex 和 OpenLaszlo。首先，您需要编写能够接收并缓存连接的后端服务器。在这里不能太过偏离主题，因而要保证服务器基于阻塞 I/O。

您需要创建一个服务器套接字，接收预先指定地址的连接：
清单 1. 创建服务器套接字
```java
public class SimpleServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket();
        serverSocket.bind(new InetSocketAddress("localhost",20340));
        Socket socket = serverSocket.accept();
    }
}
```
在这里，我将服务器套接字绑定到 localhost:20340 这一地址。当一个客户端连接到该服务器套接字时，它将为我提供一个套接字，显示连接。Flex 客户端随后会要求策略文件，这是其安全性模型的一部分。通常，这个策略文件的形式类似于清单 2。

清单 2. Flex 客户端策略文件
```xml
<?xml version="1.0"?>
<!DOCTYPE cross-domain-policy SYSTEM 
    "http://www.adobe.com/xml/dtds/cross-domain-policy.dtd">
<cross-domain-policy> 
<allow-access-from domain="*" to-ports="20340"/> 
</cross-domain-policy>
```
就在连接之后，Flex 客户端会立即发送一条策略文件的请求。该请求仅包含一个 XML 标记：<policy-file-request/>。在响应中，您需要返回此策略文件。清单 3 中的代码就完成了这个任务。

清单 3. 发送策略文件响应
```java
public static void main(String[] args) throws IOException {
   ServerSocket serverSocket = new ServerSocket();
   serverSocket.bind(new InetSocketAddress("localhost", 20340));
   Socket socket = serverSocket.accept();
   String POLICY_REQUEST = "<policy-file-request/>\u0000";
   String POLICY_FILE = "<?xml version=\"1.0\"?>\n" +
      "<!DOCTYPE cross-domain-policy SYSTEM 
         \"http://www.adobe.com/xml/dtds/cross-domain-policy.dtd\">\n" +
      "<cross-domain-policy> \n" +
      " <allow-access-from domain=\"*\" to-ports=\"20340\"/> \n" +
      "</cross-domain-policy>";
   byte[] b = new byte[POLICY_REQUEST.length()];
   DataInputStream dataInputStream = new DataInputStream(socket.getInputStream());
   dataInputStream.readFully(b);
   String request = new String(b);
   if (POLICY_REQUEST.equals(request)) {
       DataOutputStream dataOutputStream = new DataOutputStream(socket.getOutputStream());
       dataOutputStream.write(POLICY_FILE.getBytes());
       dataOutputStream.flush();
       dataOutputStream.close();
   } else throw new IllegalArgumentException("unknown request format " + request);
 }
 ```
 此代码建立了与客户端的成功连接。现在，服务器可以与客户端发起 “握手” 之类的协议，此时，服务器通常会指定一个惟一的 ID，并将其发送给客户端，此后，服务器可根据 ID 缓存套接字，在此之后，如果服务器需要向客户端推送某些数据，可以按照 ID 定位套接字，并使用其输出流。幸运的是，OpenLaszlo 也使用了相同的基于策略文件的机制，因而，同样的服务器代码适用于两种场景。

下面将介绍如何创建 Flex 套接字，随后将其与 Ajax 应用程序连接。
使用 Adobe Flex 打开客户端套接字
清单 4 中的代码展示了如何通过 Flex 打开客户端套接字：

清单 4. 通过 Flex 打开客户端
```javascript
var socket : XMLSocket = new XMLSocket();
// register events:
socket.addEventListener(Event.CLOSE, closehandler);
socket.addEventListener(Event.CONNECT, connectHandler);
socket.addEventListener(Event.OPEN, openHandler);
socket.addEventListener(ProgressEvent.SOCKET_DATA, readHandler);
socket.addEventListener(SecurityErrorEvent.SECURITY_ERROR, securityErrorHandler);
socket.connect("localhost",20340);
```
完成 socket.connect() 调用后，Flex 将向服务器发送一条请求，要求提供策略文件，期待获得 XML 响应。完成之后，连接即建立，这个套接字现在即可用于从服务器推送数据。

作为拼图的最后一块，您将看到 Flex 如何将 Ajax 作为应用程序调用。为此，要编写一个可处理服务器端消息的通用 JavaScript 函数。我们将此方法命名为 handleServerMessageReceived(message)。此方法会获取来自服务器的 XML 代码，此方法对于消息的处理方式以应用程序为依据。清单 5 中的代码展示了 Flex 如何调用 JavaScript 函数。这是 readHandler 方法的代码，该方法在接收到服务器 XML 消息时被调用。

清单 5. 使用 handleServerMessageReceived(message) 的 readhHandler 代码
```javascript
public  function readHandler(e :  DataEvent) : void {
  var message   : XML = e.data as XML;
  ExternalInterface.call("handleServerMessageReceived", message);
}
```
就是这样！就是这样简单。您已经创建了一个 XML 套接字连接。当来自服务器的数据送达时，您可调用 Ajax 中的某些通用处理函数，处理这些消息。完整源代码可供下载（请参见 下载 部分）。

下面来看看 OpenLaszlo 如何实现相同的目标。

使用 OpenLaszlo 打开客户端套接字
由于 OpenLaszlo 应用程序以 Flash 和 DHTML 平台为目标，因而其 API 和脚本语言类似于 Flash 和 JavaScript。这主要是为希望迁移到 OpenLaszlo（作为 RIA 的替代方案）的 Web 开发人员提供便利。

OpenLaszlo 提供了两种创建与后端之间的持久连接的方法。一种方法要使用 Lz（Laszlo 的缩写）标准库中提供的 ConnectionManager API。但其文档明确说明了以下内容：

“警告：这项特性是临时的。此特性用于容量有限的环境，能够用于开发，但我们不推荐使用此特性进行部署（不包括低容量、非任务关键型的部署）。若对使用此版本的持久连接的应用程序的健壮性有任何问题，请直接咨询 Laszlo Systems。”

或许目前这是一项实验技术，但在未来的 OpenLaszlo 版本中，它将得到证实。

第二种方法与 Flex 相似，您要手动打开 XML 套接字连接，等待 READ_DATA 事件发生。清单 6 展示了实现方法。

清单 6. 定义 XMLSocket 类
```javascript
<class name="ClientSocket" extends="node">
    <attribute name="host" />
    <attribute name="port" />
    <XMLSocket name='xml_socket'/>
    <handler name="oninit">
        // connect the socket here:
        xml_socket.connect(host,port);
    </handler>
    <handler name='onData' reference='xml_socket' args='messageXML'>
 <![CDATA[
        ExternalInterface.call(‘handleServerMessageReceived',messageXML);
    ]]>
    </method> 
</class>
```
（为简短起见，忽略了其他处理方法。在本文的 下载 部分中可获得完整的代码清单。）

就是这样，创建一个套接字对象并连接此对象就是这样轻松。这一代码清单创建了一个名为 ClientSocket 的新类，随后声明了一个名为 “xml_socket” 的 XML 套接字对象。只要此套接字对象读取到来自服务器的数据，就会触发 onData 事件，该事件将由为 onData 定义的处理方法处理。最后，在 onData 处理方法中，调用 Ajax 应用程序中的外部 JavaScript 函数。此后的流程与 Flex 客户端相同。

要创建 ClientSocket 对象，只需声明它即可：

清单 7. 声明 ClientSocket
```javascript
<canvas>
    <ClientSocket id='serverPushSocket' host='localhost' port='20340'/>
</canvas>
```
为 ClientSocket 触发了 init 事件时，将尝试连接指定主机和端口的后端。（请参见清单 6 中的 oninit 处理方法。）

结束语
这篇文章讨论了几种模拟服务器推送的方法，从纯轮询到实时服务器推送，文中说明了每种方法的优缺点。最后，我重点关注了能够提供最优服务器可伸缩性和实时服务器推送行为的方法。

服务器推送并非适用于每一个应用程序。实际上，大多数应用程序都非常适合普通的请求/响应场景。其他一些应用程序使用轮询和类似的技术足以满足需求。只有那些服务器更新极为重要、客户端需要得到即时通知的重量级应用程序才需要本文所述技术。有必要再次强调，这种技术有两个主要的缺点：

如果数据需要通过 HTTPS 传输，客户端套接字无法利用 SSL 加密工具。
防火墙需要允许客户端套接字通过非标准端口（非 80 端口）连接到服务器。
然而，市面上存在着大量开源库，您可利用它们轻松编写自定义的加密例程。类似地，配置防火墙也是轻而易举的，实际上，只需付出很少的代价，即可获得强大的实时服务器推送功能。

下载资源[源代码 (samples.zip | 9KB)](http://www.ibm.com/developerworks/apps/download/index.jsp?contentid=446627&filename=samples.zip&method=http&locale=zh_CN)
相关主题
在 Adobe Flash 文档 中进一步了解二进制套接字 API。
在 Adobe Flash 文档 中进一步了解 XML Socket API。
阅读文章 “Setting Up A Flash Socket Policy File”，进一步了解配置套接字策略文件的信息。
阅读 “Action Script Cook Book” 一书的第 24 章，进一步了解套接字编程。
访问 产品站点，了解 OpenLaszlo 持久连接的更多信息。
获得关于 Adobe Flex 的更多信息。
developerWorks 技术活动和网络广播：随时关注 developerWorks 技术活动和网络广播。
developerWorks Web development 专区：通过专门关于 Web 技术的文章和教程，扩展您在网站开发方面的技能。


