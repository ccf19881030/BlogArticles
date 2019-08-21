## [CentOS7 防火墙相关操作与端口配置 （收集+持续更新）](https://blog.csdn.net/llwy1428/article/details/99676257)
一、防火墙 开启、关闭、查看状态

1、开启防火墙

[root@localhost ~]# systemctl start firewalld

2、关闭防火墙

[root@localhost ~]# systemctl stop firewalld

3、重启防火墙

[root@localhost ~]# systemctl start firewalld

4、查看防火墙当下的状态

[root@localhost ~]# systemctl status firewalld
