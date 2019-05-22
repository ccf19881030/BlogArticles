# [如何在Ubuntu 18.04中安装MySQL 8.0数据库服务器](https://www.linuxidc.com/Linux/2018-11/155408.htm)
## 第1步：添加MySQL Apt存储库
目前已经有了现成可用于安装 MySQL Server、客户端和其它组件的 APT 存储库，我们需要先将 MySQL 存储库添加到 Ubuntu 18.04 的软件包源列表中：

1、先使用 wget 下载存储库软件包：
```shell
wget -c https://dev.mysql.com/get/mysql-apt-config_0.8.10-1_all.deb
```
## 2、然后使用以下 dpkg 命令安装下载好的 MySQL 存储库软件包：
```shell
sudo dpkg -i mysql-apt-config_0.8.10-1_all.deb
```
注意：在软件包安装过程中，系统会提示您选择 MySQL 服务器版本和其他组件，例如群集、共享客户端库或配置要安装 MySQL 的工作台。

默认 MySQL 服务器版本 mysql-8.0 的源将被自动选中，我们只需最终确定就可以完成发行包的配置和安装。

第1步：在Ubuntu 18.04中安装MySQL 8服务器
1、从所有已配置的存储库（包括新添加的 MySQL 8存储库）中下载最新的软件包信息：
```shell
sudo apt update
2、然后运行如下命令安装 MySQL 8 社区服务器、客户端和数据库公用文件：
```shell
sudo apt-get install mysql-server
```
3、通过安装过程，将会要求为 MySQL 8 服务器的 root 用户输入密码，在输入和再次验证后按回车继续。
4、接下来，MySQL 服务器认证插件的配置信息将会出现，用键盘右键选择 OK 后按回车继续。
5、此后，需要选择将要使用的默认身份认证插件，选择好之后按回车即可完成程序包配置。
MySQL 8使用基于改进的基于SHA256的新身份验证
  │密码方法。 建议所有新的MySQL服务器
  │安装使用这种方法。 这个新认证
  │插件需要新版本的连接器和客户端，并支持
  │这种新的身份验证方法（caching_sha2_password）。 目前是MySQL
  │8使用libmysqlclient21支持构建的连接器和社区驱动程序

身份认证插件有如下 2 种可供选择：

使用存储密码加密（推荐）
使用传统认证模式（MySQL 5.x 兼容）
第3步：运行安全的 MySQL 8.0服务器
默认安装的 MySQL 服务器都是不太安全的，为了提供基本的安全保障，请运行二进制安装包中附带的安全脚本进行一些基本配置。（执行脚本时需要验证安装过程中已配置的 root 密码，然后选择是否使用 VALIDATE PASSWORD 插件。）

脚本执行后可以更改之前设置的 root 密码，然后执行 y 来解决如下安全问题：

Remove anonymous users? : y（删除匿名用户）
Disallow root login remotely?: y（禁止root远程登录）
Remove test database and access to it? : y（删除测试数据库）
Reload privilege tables now? : y（立即重新加载特权表）
sudo mysql_secure_installation

第4步：通过Systemd管理MySQL 8
在 Ubuntu 系统中，通常安装好的服务都是被配置为自动启动的，您可以使用如下命令检查 MySQL 服务器是否已启动并正在运行。

linuxidc@ubuntu:~$ sudo systemctl status mysql
[sudo] password for linuxidc: 
● mysql.service - MySQL Community Server
  Loaded: loaded (/lib/systemd/system/mysql.service; enabled; vendor preset: en
  Active: active (running) since Mon 2018-11-19 22:22:56 PST; 12min ago
    Docs: man:mysqld(8)
          http://dev.mysql.com/doc/refman/en/using-systemd.html
  Process: 4105 ExecStartPre=/usr/share/mysql-8.0/mysql-systemd-start pre (code=
 Main PID: 4144 (mysqld)
  Status: "SERVER_OPERATING"
    Tasks: 38 (limit: 2293)
  CGroup: /system.slice/mysql.service
          └─4144 /usr/sbin/mysqld

Nov 19 22:22:55 ubuntu systemd[1]: Starting MySQL Community Server...
Nov 19 22:22:56 ubuntu systemd[1]: Started MySQL Community Server.
lines 1-14/14 (END)
如果由于一些原因没有自动启动，可以用如下命令手动启用并将 MySQL 8 配置为随系统启动时启动：

sudo systemctl status mysql
sudo systemctl enable mysql

第5步：安装额外的MySQL产品和组件
另外，如果有需要，也可以安装额外的 MySQL 组件，以便与服务器一起工作。比如 mysql-workbench-community 和libmysqlclient18 等等。

sudo apt-get update

sudo apt-get install mysql-workbench-community libmysqlclient18

更多详细请参考，MySQL 8.0 发行日志。

Linux公社的RSS地址：https://www.linuxidc.com/rssFeed.aspx

本文永久更新链接地址：https://www.linuxidc.com/Linux/2018-11/155408.htm
