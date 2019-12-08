## [Qt之FTP上传和下载文件操作](https://zhuanlan.zhihu.com/p/92496797)
一个简单的Ftp客户端文件上传/下载操作示例。
### 上传文件
```cpp
QNetworkAccessManager manager;
QUrl url;
/* 设置通讯协议 */
url.setScheme("ftp");    
/* 设置用户名 */  
url.setUserName("root");  
/* 设置密码 */ 
url.setPassword("123456"); 
/* 设置主机，也可以是域名 */
url.setHost("127.0.0.1");
/* 设置端口号，一般为21 */  
url.setPort(21);         
/* 设置路径 */ 
url.setPath("/tmp/hello.png"); 

/* 装载本地文件 */
QFile file("/Desktop/hello.png"); 
file.open(QIODevice::ReadOnly);
/* 读取本地文件数据 */
QByteArray data = file.readAll(); 
file.close();

QNetworkRequest request(url);
/* 上传数据，上传成功后会在远端创建/tmp/hello.png文件 */
QNetworkReply* reply = manager.put(request, data); 

QEventLoop eventLoop; 
QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
/* 进入等待，但事件循环依然进行 */
eventLoop.exec(); 

if (reply->error() != QNetworkReply::NoError) {
    qDebug() << "Error: " << reply->errorString();
}
```

### 下载文件
```cpp
QNetworkAccessManager manager;
QUrl url;
/* 设置通讯协议 */
url.setScheme("ftp");      
/* 设置用户名 */
url.setUserName("root");   
/* 设置密码 */
url.setPassword("123456"); 
/* 设置主机，也可以是域名 */
url.setHost("127.0.0.1");  
/* 设置端口号，一般为21 */
url.setPort(21);           
/* 设置路径 */
url.setPath("/tmp/test.txt"); 

QNetworkRequest request(url);
/* 执行Get请求 */
QNetworkReply* reply = manager.get(request); 

QEventLoop eventLoop;
QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
/* 进入等待，但事件循环依然进行 */
eventLoop.exec(); 

if (reply->error() == QNetworkReply::NoError) {
    /* 创建本地文件 */
    QFile file("test.txt"); 
    file.open(QIODevice::WriteOnly);
    /* 写入文件 */
    file.write(reply->readAll()); 
    file.close();
}
else {
    qDebug() << "Error: " << reply->errorString();
}
```

### 总结
上传文件：配置url->加载数据->put操作
下载文件：配置url->get操作->获取数据保存到文件
如服务端没有身份验证，客户端可以省略用户名和密码操作。
