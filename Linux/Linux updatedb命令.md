# [关于updatedb命令和locate命令的问题](https://blog.csdn.net/qq_39513105/article/details/81710802)
在CentOS-7中使用locate命令发现没有这个命令, 就去安装但是也不可安装

这就需要使用updatedb更新一下文件库, 运行这个命令发现也不存在

所以就yum安装, 发现还是不存在

这是你就需要去安装一下mlocate

命令如下:
```shell
yum -y install mlocate

yum -y install updatedb

updatedb

locate inittab
```
接下来就可以使用了 。
locate 是非实时的模糊查询, 根据全系统文件的数据库进行,但是locate的速度是快于find的。
