## [xampp的MySQL与电脑中已有的MySQL冲突](https://blog.csdn.net/qq_20757489/article/details/86668190)
## [XAMPP中MySQL和本地MySQL冲突的解决方案](https://blog.csdn.net/sinat_37633633/article/details/77645463)
环境：Windows+xmapp7.1

在网上找了很多更改端口的办法失败，而且很麻烦，并且我又不想卸载本地的MySQL。现在给大家提供一种不改端口的解决方法，操作比较方便

### 实现步骤：

* ①运行regedit
* ②找到HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\MySQL
* ③更改ImagePath为"D:\xampp\mysql\bin\mysqld" --defaults-file="D:\xampp\mysql\bin\my.ini" MySQL
* ④保存即可使用xampp中的MySQL

### 如果后面启动不了，出现以下错误：
```shell
Error: MySQL shutdown unexpectedly.
11:42:54  [mysql] This may be due to a blocked port, missing dependencies, 
11:42:54  [mysql] improper privileges, a crash, or a shutdown by another method.
11:42:54  [mysql] Press the Logs button to view error logs and check
11:42:54  [mysql] the Windows Event Viewer for more clues
11:42:54  [mysql] If you need more help, copy and post this
11:42:54  [mysql] entire log window on the forums
```


### 解决办法：
打开D:\xampp\mysql\bin\my.ini文件，将目录/xampp都替换成D:/xampp，即加上盘符，使成完整路径。
注意：

此种方法更改了注册表路径 ，即将原来的MySQL注册表路径改为xampp的MySQL注册表路径，本地的MySQL暂时不能使用，日后需要使用再将此路径更改回来"C:\Program Files\MySQL\MySQL Server 5.5\bin\mysqld --defaults-file="C:\Program Files\MySQL\MySQL Server 5.5\my.ini" MySQL 即可。

我也是花了很久时间才解决这个问题，希望能够帮助到大家，多点时间花在核心业务上，别浪费时间配置环境。
