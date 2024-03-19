# NModbus-一个基于C#实现的Modbus通信协议库

最近在学习C#的时候，因为之前做过环保设备时使用C++做过环保设备采集使用到了Modbus协议，当时看了一下基于C语言开发的[libmodbus](https://github.com/stephane/libmodbus)库。所以特意搜索看了一下C#下有什么Modbus协议库，在Github上面找了一下，有一个[NModbus](https://github.com/NModbus/NModbus)的源代码，亲测可以在VS2022中完美运行。实际测试过程中可以用Modbus Slave或Modbus Poll等工具进行配合测试。[NModbus](https://www.nuget.org/packages/Modbus)提供与 Modbus 从站兼容设备和应用程序的连接。支持串口 ASCII、串口 RTU、串口 USB ASCII、串口 USB RTU、TCP 和 UDP 协议。非常值得我们去学习。
在C#中`NuGet`程序控制台命令行安装如下：
```
 Install-Package NModbus
```
特此记录一下
![NModbus协议库](https://img-blog.csdnimg.cn/direct/8fdaeabff9ab427cb575bcffe3c1e22a.png)
![NModbus NuGet](https://img-blog.csdnimg.cn/direct/f093032b7c2e45149eaedf5a9a84b86d.png)

## 参考资料
- [NModbus](https://github.com/NModbus/NModbus)
-  [Modbus library](https://www.nuget.org/packages/Modbus)
- [https://nmodbus.github.io/api/NModbus.html](https://nmodbus.github.io/api/NModbus.html)
- [libmodbus-A Modbus library for Linux, Mac OS, FreeBSD and Windows](https://github.com/stephane/libmodbus)
- [libmodbus.org](http://libmodbus.org/)
